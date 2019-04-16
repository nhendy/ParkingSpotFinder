from app import db
from app.main import bp
from flask import render_template, request, flash,  redirect, url_for
from flask_login import current_user, login_user, logout_user, login_required
from app.models import User



@bp.route('/')
@bp.route('/index')
def index():
    return render_template('booking/index.html')


@bp.route('/option_to_book')
@login_required
def option_to_book():
    return render_template('booking/index_ParkMe.html')



@bp.route('/book_spot', methods=('GET', 'POST'))
@login_required
def book_spot():
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
            return redirect(url_for('main.index'))

    return render_template('booking/book_spot.html')
