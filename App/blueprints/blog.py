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
        print("user: ")
        print(g.user)
        if error is not None:
            flash(error)
        else:
            return redirect(url_for('blog.index'))
    return render_template('blog/bookSpot.html')