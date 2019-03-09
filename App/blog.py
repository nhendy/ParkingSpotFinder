from flask import (
    Blueprint, flash, g, redirect, render_template, request, url_for)
import db
from werkzeug.exceptions import abort
import functools
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

@bp.route('/show_spot_state', methods=('GET','POST'))
def show_spots():
    engine = create_engine('sqlite:///parkingSpotsDB.db')

    Base = automap_base()
    Base.prepare(engine, reflect=True)
    Table = Base.classes.spots

    DBSession = sessionmaker(bind=engine)
    session = DBSession()
    stmt = select('*').select_from(Table)
    result = session.execute(stmt).fetchall()
    result = str(result_dicts(result))
    return str(result)
#****************************************************
@bp.route('/')
def index():
    return render_template('blog/startingPage.html')

@bp.route('/option_to_book')
def option_to_book():
    return render_template('blog/indexParkMe.html')

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

@bp.route('/update_spots',methods=('GET', 'POST'))
@auth_pi
def update_spots():
    if request.method == 'POST':
        content = request.json
        occupied_spots = content["occupied"]
        update_spots_occ(occupied_spots)
        return "updated"

@bp.route('/init_parking_spot_db', methods=('GET','POST'))
@auth_pi
def init_spot_db():
    if request.method == 'POST':
        content = request.json
        spots_info = content["spot_ids"]
        initialize_spot_db(spots_info)
        return "initialized"

def initialize_spot_db(spot_ids):
    sql_session = db.load_db("parkingSpotsDB")
    for ID in spot_ids:
        new_spot = app.Spots(spot_id=ID,state="vacant")
        sql_session.add(new_spot)
        sql_session.commit()

def update_spots_occ(occupied_spots):
    sql_session = db.load_db("parkingSpotsDB")
    for ID in occupied_spots:
        user = sql_session.query.filter_by(spot_=ID).first()
        print(user.state)

@bp.route('/bookSpot', methods=('GET', 'POST'))
# @login_required
def bookSpot():
    if request.method == 'POST':
        error = None
        if error is not None:
            flash(error)
        else:
            # user request data
            sql_session = db.load_db("parkingSpotsDB")
            new_person = app.RequestsRecord(id=23, name=g.user['id'])
            sql_session.add(new_person)
            sql_session.commit()
            return redirect(url_for('blog.index'))

    return render_template('blog/bookSpot.html')