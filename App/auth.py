import functools
import db
from flask import (
    Blueprint, flash, g, redirect, render_template, request, session, url_for
)
from werkzeug.security import check_password_hash, generate_password_hash
import app
from sqlalchemy.ext.automap import automap_base
from sqlalchemy import Column, ForeignKey, Integer, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, sessionmaker
from sqlalchemy import create_engine, select
bp = Blueprint('auth', __name__, url_prefix='/auth')

#*********** HELPER FUNCTIONS ********************#
def result_dict(r):
    return dict(zip(r.keys(), r))

def result_dicts(rs):
    return list(map(result_dict, rs))

@bp.route('/show_me_users', methods=('GET','POST'))
def show_users():
    engine = create_engine('sqlite:///userCredentialsDB.db')

    Base = automap_base()
    Base.prepare(engine, reflect=True)
    Table = Base.classes.users

    DBSession = sessionmaker(bind=engine)
    session = DBSession()
    stmt = select('*').select_from(Table)
    result = session.execute(stmt).fetchall()
    result = str(result_dicts(result))
    return str(result)
#*************************************************#

@bp.route('/register', methods=('GET', 'POST'))
def register():
    if request.method == 'POST':
        Username = request.form['username']
        Password = request.form['password']

        if not Username:
            error = 'Username is required.'
        elif not Password:
            error = 'Password is required.'

        session = db.load_db("UserCredentialsDB")
        new_person = app.Users(username=Username, password=Password)
        session.add(new_person)
        session.commit()
        session.close

        error = None

        if error is None:
            return redirect(url_for('auth.login'))

        flash(error)

    return render_template('auth/register.html')

@bp.route('/login', methods=('GET', 'POST'))
def login():
    if request.method == 'POST':
        Username = request.form['username']
        Password = request.form['password']

        error = None
        try:
            session = db.load_db("UserCredentialsDB")
            user = session.query(app.Users).filter_by(username=Username)
            if user is None:
                error = "Unregistered user"
            elif not (user.password == Password):
                error = "Incorrect Password"
        except:
            pass

        if error is None:
            return redirect(url_for('blog.index'))

        flash(error)
    return render_template('auth/login.html')

@bp.route('/logout')
def logout():
    return redirect(url_for('blog.index'))
