from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_migrate import Migrate
from flask_login import LoginManager
import os
from flask_admin import Admin
from flask_admin.contrib.sqla import ModelView
from flask_security import Security, SQLAlchemyUserDatastore, utils
from app.admin.view import AdminView
from flask_user import UserManager
import datetime

app = Flask(__name__)
app.config.from_object(os.environ['APP_SETTINGS'])
db = SQLAlchemy(app)
migrate = Migrate(app, db)
login = LoginManager(app)
login.login_view = 'auth.login'


from app.auth import bp as auth_bp
app.register_blueprint(auth_bp, url_prefix='/auth')

from app.main import bp as main_bp
app.register_blueprint(main_bp)


from app.models import User, Role
# user_datastore = SQLAlchemyUserDatastore(db, User, Role)
# security = Security(app, user_datastore)


admin = Admin(app, name='parkme', template_mode='bootstrap3')
admin.add_view(AdminView(User, db.session))
admin.add_view(AdminView(Role, db.session))

# Executes before the first request is processed.
@app.before_first_request
def before_first_request():
    db.create_all()
    #
    # admin = User(username='admin', email='admin@admin.edu')
    # admin.set_password('admin_password')
    # # admin.roles.append("admin")
    # db.session.add(admin)
    # db.session.commit()

@app.before_request
def before_request():
    reserved_users = User.query.filter_by(reserved=True).all()
    for user in reserved_users:
        difference = datetime.datetime.utcnow() - datetime.datetime.strptime(str(user.timestamp),'%Y-%m-%d %H:%M:%S.%f')
        if difference.total_seconds() > 600:
            user.reserved = False
            user.code = -1
            db.session.commit()