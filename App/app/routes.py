from app import app, db
from flask import render_template, request, flash,  redirect, url_for
from app.forms import RegistrationForm, LoginForm
from flask_login import current_user, login_user, logout_user, login_required
from app.models import User

@app.route('/')
@app.route('/index')
def index():
    return render_template('booking/index.html')

@app.route('/register', methods=('GET', 'POST'))
def register():
    if current_user.is_authenticated:
        return redirect(url_for('index'))

    form = RegistrationForm()
    if form.validate_on_submit():
        user = User(username=form.username.data)
        user.set_password(form.password.data)
        db.session.add(user)
        db.session.commit()
        flash('Congratulations, you are now a registered user!')
        return redirect(url_for('login'))

    return render_template('auth/register.html', form=form)

@app.route('/login', methods=('GET', 'POST'))
def login():
    if current_user.is_authenticated:
        return redirect(url_for('index'))
    form = LoginForm()
    if form.validate_on_submit():
        user = User.query.filter_by(username=form.username.data).first()
        if user is None or not user.check_password(form.password.data):
            flash('Invalid username or password')
            return redirect(url_for('login'))
        login_user(user, remember=True)
        return redirect(url_for('index'))
    return render_template('auth/login.html', form=form)


@app.route('/logout')
def logout():
    logout_user()
    return redirect(url_for('index'))


@app.route('/option_to_book')
@login_required
def option_to_book():
    return render_template('booking/index_ParkMe.html')



@app.route('/book_spot', methods=('GET', 'POST'))
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
            return redirect(url_for('index'))

    return render_template('booking/book_spot.html')
