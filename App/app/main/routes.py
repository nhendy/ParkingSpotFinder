from app import db
from app.main import bp
from flask import render_template, request, flash,  redirect, url_for, jsonify
from flask_login import current_user, login_user, logout_user, login_required
from app.models import User
from flask_user import roles_required
import datetime
import random, functools
from flask import current_app


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
    # TODO FIXME check expiration
    if current_user.is_authenticated:
        user = User.query.filter_by(username=current_user.username).first()
        user.reserved = True
        user.timestamp = datetime.datetime.utcnow()
        user.code = random.randint(1,1001)
        db.session.commit()
        code_gen = "your code is: "
    else:
        return redirect(url_for('main.index'))
    return render_template('booking/book_spot.html',code = code_gen + str(user.code))

def check_credentials(credentials):
    print(value)
    if credentials.username == "rpi" and credentials.password == "password":
        return True
    return False

def auth_pi(view):
    @functools.wraps(view)
    def decorated(*args, **kwargs):
        if not current_user.is_authenticated:
           return current_app.login_manager.unauthorized()

        if current_user.roles[0].name != 'RPi':  #TODO FIXME !!!!!!
             return current_app.login_manager.unauthorized()
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
        app.vacant_spot_count = content["vacant_spot_count"]
        if content["request_for_reserved_spots"] == "True":
            result_dict["num_spots_reserved"] = get_reserved_spot_count()
            result_dict["code_validation"] = None
        else:
            result_dict["code_validation"] = check_code(content["code_generated"])
            result_dict["num_spots_reserved"] = 0
        return jsonify(result_dict)
    return jsonify({"error": "request not POST method",
                    "reason": "request should be post, json format"})
