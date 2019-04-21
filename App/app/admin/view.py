from flask_admin.contrib import sqla
from flask_security import current_user
from flask import redirect, url_for

class AdminView(sqla.ModelView):
    # pass
    def is_accessible(self):
        return current_user.is_authenticated
        # # user = User.query.filter_by(username=current_user.name).first()
        # if current_user == "admin":
        #     return current_user.is_authenticated
        # logout_user

    def inaccessible_callback(self, name, **kwargs):
        return redirect(url_for('auth.login'))