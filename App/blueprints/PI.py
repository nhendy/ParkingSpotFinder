from flask import (
    Blueprint, flash, g, redirect, render_template, request, url_for, jsonify)
import db
import datetime
from werkzeug.exceptions import abort
import functools
from sqlalchemy.ext.automap import automap_base
from sqlalchemy import Column, ForeignKey, Integer, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, sessionmaker
from sqlalchemy import create_engine, select, exists
import app
bp = Blueprint('PI', __name__,url_prefix='/PI')

############## HELPERS ###############

@bp.route('/hello',methods=('GET','POST'))
def hello():
    return "hello tania"

def result_dict(r):
    return dict(zip(r.keys(), r))

def result_dicts(rs):
    return list(map(result_dict, rs))

def get_users_data_as_dict():
    engine = create_engine('sqlite:///userCredentialsDB.db')

    Base = automap_base()
    Base.prepare(engine, reflect=True)
    Table = Base.classes.users

    DBSession = sessionmaker(bind=engine)
    session = DBSession()
    stmt = select('*').select_from(Table)
    result = session.execute(stmt).fetchall()
    result = (result_dicts(result))
    return (result)

######################################

def check_credentials(credentials):
    if credentials.username == "username" and credentials.password == "1234":
        return True
    return False

def auth_pi(view):
    @functools.wraps(view)
    def decorated(*args, **kwargs):
        if request.method == 'POST':
            auth = request.authorization
            if not auth or not check_credentials(auth):
                return "your credentials were incorrect"
            return view(*args, **kwargs)
    return decorated

@bp.route('/pi_to_app', methods=('GET', 'POST'))
@auth_pi
def pi_to_app():
    if request.method == 'POST':
        try:
            content = request.get_json()
        except Exception as e:
            return jsonify({"error": str(e),
                            "reason": "request should be json format"})
        result_dict = dict()
        if content["request_for_reserved_spots"] == "True":
            result_dict["num_spots_reserved"] = get_reserved_spot_count()
            result_dict["code_validation"] = None
        else:
            result_dict["code_validation"] = check_code(content["code_generated"])
            result_dict["num_spots_reserved"] = 0
        return jsonify(result_dict)
    return jsonify({"error": "request not POST method",
                    "reason": "request should be post, json format"})

def check_code(code_generated):
    sql_session = db.load_db("UserCredentialsDB")
    check = sql_session.query(exists().where(app.Users.code == code_generated)).scalar()
    if check:
        sql_session.query(app.Users).filter(app.Users.code == code_generated). \
            update({app.Users.reservation_state: "unreserved"}, synchronize_session=False)
        sql_session.commit()
        return "okay"
    return "not_okay"

def get_reserved_spot_count():
    sql_session = db.load_db("UserCredentialsDB")
    update_expired_spots(sql_session)
    ### there has got to be a better way to do this
    data = get_users_data_as_dict()
    count = 0
    for row in data:
        if row["reservation_state"] == "reserved":
            count += 1
    #print(count)
    return count

def update_expired_spots(sql_session):
    timenow = datetime.datetime.utcnow()
    data = get_users_data_as_dict()
    for row in data:
        difference = timenow - datetime.datetime.strptime(row["timestamp"],'%Y-%m-%d %H:%M:%S.%f')
        if difference.total_seconds() > 600:
            sql_session = db.load_db("UserCredentialsDB")
            sql_session.query(app.Users).filter(app.Users.username == row["username"]). \
                update({app.Users.reservation_state: "unreserved"}, synchronize_session=False)
            sql_session.commit()

