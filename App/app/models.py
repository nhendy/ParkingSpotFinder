from app import db, login
from sqlalchemy.dialects.postgresql import JSON
from flask_login  import UserMixin
from werkzeug.security import generate_password_hash, check_password_hash
from datetime import datetime
from functools import wraps

class User(db.Model, UserMixin):
    __tablename__ = 'Users'
    id             = db.Column(db.Integer,primary_key=True)
    username       = db.Column(db.String(250), nullable=False, unique=True)
    active         = db.Column('is_active', db.Boolean(), nullable=False, server_default='1')
    email          = db.Column(db.String(255), unique=True, nullable=True)   #TODO FIXME
    password_hash  = db.Column(db.String(250), nullable=False)
    reserved       = db.Column(db.Boolean, nullable=False, default=False)
    timestamp      = db.Column(db.DateTime, nullable=False, default=datetime.utcnow)
    code           = db.Column(db.Integer)
    roles          = db.relationship('Role', secondary='user_roles')

    def __init__(self, username, email):
        self.username = username
        self.email = email

    def __repr__(self):
        return '<id {}, username {}>'.format(self.id, self.username)

    def set_password(self, password):
        self.password_hash    = generate_password_hash(password)

    def check_password(self, password):
        return check_password_hash(self.password_hash, password)

# Define the Role data-model
class Role(db.Model):
    __tablename__ = 'roles'
    id = db.Column(db.Integer(), primary_key=True)
    name = db.Column(db.String(50), unique=True)

    def __str__(self):
        return self.name

# Define the UserRoles association table
class UserRoles(db.Model):
    __tablename__ = 'user_roles'
    id = db.Column(db.Integer(), primary_key=True)
    user_id = db.Column(db.Integer(), db.ForeignKey('Users.id', ondelete='CASCADE'))
    role_id = db.Column(db.Integer(), db.ForeignKey('roles.id', ondelete='CASCADE'))

@login.user_loader
def load_user(id):
    return User.query.get(int(id))