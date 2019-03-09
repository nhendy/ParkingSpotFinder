from flask import (
    Blueprint, flash, g, redirect, render_template, request, url_for
)
from werkzeug.exceptions import abort
import functools
from sqlalchemy import Column, ForeignKey, Integer, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, sessionmaker
from sqlalchemy import create_engine
import app
bp = Blueprint('blog', __name__)

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
        update_spots(occupied_spots)

def update_spots(occupied_spots):
    return "yes!"

@bp.route('/bookSpot', methods=('GET', 'POST'))
# @login_required
def bookSpot():
    if request.method == 'POST':
        title = request.form['title']
        body = request.form['body']
        error = None

        if error is not None:
            flash(error)
        else:
            # user request data
            engine = create_engine('sqlite:///userRequestsDB.db')
            app.Base.metadata.bind = engine
            DBSession = sessionmaker(bind=engine)
            session = DBSession()
            new_person = app.RequestsRecord(id=23, name=g.user['id'])
            session.add(new_person)
            session.commit()
            return redirect(url_for('blog.index'))

    return render_template('blog/bookSpot.html')