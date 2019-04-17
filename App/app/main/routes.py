from app import db
from app.main import bp
from flask import render_template, request, flash,  redirect, url_for
from flask_login import current_user, login_user, logout_user, login_required
from app.models import User
from flask_user import roles_required


# Executes before the first request is processed.
@bp.before_first_request
def before_first_request():

    # Create any database tables that don't exist yet.
    db.create_all()

    # Create the Roles "admin" and "end-user" -- unless they already exist
    user_datastore.find_or_create_role(name='admin', description='Administrator')
    user_datastore.find_or_create_role(name='end-user', description='End user')

    # Create two Users for testing purposes -- unless they already exists.
    # In each case, use Flask-Security utility function to encrypt the password.
    encrypted_password = utils.encrypt_password('password')
    if not user_datastore.get_user('someone@example.com'):
        user_datastore.create_user(email='someone@example.com', password=encrypted_password)
    if not user_datastore.get_user('admin@example.com'):
        user_datastore.create_user(email='admin@example.com', password=encrypted_password)

    # Commit any database changes; the User and Roles must exist before we can add a Role to the User
    db.session.commit()

    # Give one User has the "end-user" role, while the other has the "admin" role. (This will have no effect if the
    # Users already have these Roles.) Again, commit any database changes.
    user_datastore.add_role_to_user('someone@example.com', 'end-user')
    user_datastore.add_role_to_user('admin@example.com', 'admin')
    db.session.commit()



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


@bp.route('/pi_to_app', methods=('GET', 'POST'))
@roles_required('RPi')
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

