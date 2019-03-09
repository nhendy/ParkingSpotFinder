import functools
import db
from flask import (
    Blueprint, flash, g, redirect, render_template, request, session, url_for
)
from werkzeug.security import check_password_hash, generate_password_hash
import app
from sqlalchemy.ext.automap import automap_base
from sqlalchemy import Column, ForeignKey, Integer, String, exists
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship, sessionmaker
from sqlalchemy import create_engine, select, and_
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

        error = None

        if not Username:
            error = 'Username is required.'
        elif not Password:
            error = 'Password is required.'
        try:
            sql_session = db.load_db("UserCredentialsDB")
            new_person = app.Users(username=Username, password=Password)
            sql_session.add(new_person)
            sql_session.commit()
        except Exception as e:
            error = "could not register because: " + str(e)

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
            sql_session = db.load_db("UserCredentialsDB")
            check = sql_session.query(exists().where(and_(app.Users.username == Username, app.Users.password == Password))).scalar()
            if not check:
                error = "Unregistered user or wrong password"
            else:
                error = None
        except Exception as e:
            error = "could not log you in because: " + str(e)

        if error is None:
            session.clear()
            session['user_id'] = Username
            return redirect(url_for('blog.option_to_book'))

        flash(error)
    return render_template('auth/login.html')

@bp.before_app_request
def load_logged_in_user():
    user_id = session.get('user_id')

    if user_id is None:
        g.user = None
    else:
        sql_session = db.load_db("UserCredentialsDB")
        user = sql_session.query(app.Users).filter_by(username=user_id)
        g.user = user

@bp.route('/logout')
def logout():
    session.clear()
    return redirect(url_for('blog.index'))
