from flask_admin.contrib import sqla
from  flask_security import current_user
from flask import redirect, url_for


class AdminView(sqla.ModelView):
    def is_accessible(self):
        return current_user.has_role('admin')

    def inaccessible_callback(self, name, **kwargs):
        return redirect(url_for('auth.login'))