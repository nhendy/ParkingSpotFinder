from flask import (
    Blueprint, flash, g, redirect, render_template, request, url_for, jsonify)
import db
import random
from werkzeug.exceptions import abort
import functools
import datetime
from sqlalchemy.ext.automap import automap_base
from sqlalchemy import Column, ForeignKey, Integer, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, sessionmaker
from sqlalchemy import create_engine, select
import app
bp = Blueprint('blog', __name__)
#*******************HELPER FUNCTIONS*****************
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
#****************************************************
def update_db(name):
    sql_session = db.load_db("UserCredentialsDB")
    sql_session.query(app.Users).filter(app.Users.username == name).\
        update({app.Users.timestamp: datetime.datetime.utcnow(),
                app.Users.reservation_state: "reserved",
                app.Users.code: random.randint(1,1001)}, synchronize_session=False)
    sql_session.commit()

@bp.route('/')
def index():
    return render_template('blog/startingPage.html')

@bp.route('/option_to_book')
def option_to_book():
    update_db(g.user)
    return render_template('blog/indexParkMe.html')

@bp.route('/bookSpot', methods=('GET', 'POST'))
# @login_required
def bookSpot():
    if request.method == 'POST':
        error = None
        if error is not None:
            flash(error)
        else:
            return redirect(url_for('blog.index'))
    sql_session = db.load_db("UserCredentialsDB")
    data = get_users_data_as_dict()
    user_code = "your code is: "
    code_matched = -1
    for row in data:
        if row["username"] == g.user:
            code_matched = row["code"]
    if code_matched != -1:
        user_code = user_code + str(code_matched)
    else:
        user_code = user_code + "not found"
    return render_template('blog/bookSpot.html',code=user_code)