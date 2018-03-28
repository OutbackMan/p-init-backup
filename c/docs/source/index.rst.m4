m4_changecom()m4_dnl
m4_define(`M4_LPROJECT_NAME_M4', `m4_esyscmd(echo -n $(basename $(cat ~/.working-on)))')m4_dnl
m4_define(`M4_UPROJECT_NAME_M4', `m4_esyscmd((echo -n $(basename $(cat ~/.working-on))) | tr [a-z] [A-Z])')m4_dnl
m4_define(`M4_CURRENT_YEAR_M4', `m4_esyscmd(echo -n $(date +"%Y"))')m4_dnl
m4_define(`M4_PROJECT_DESCRIPTION_M4`, `m4_esyscmd(echo -n $(curl https://api.github.com/users/`'M4_GITHUB_USER_NAME_M4`'/repos | jq '[] | select(.name == "`'M4_LPROJECT_NAME_M4`'") | .description')m4_dnl
Welcome to `M4_LPROJECT_NAME_M4`''s documentation
=================================================

Overview
--------
'MR_LPROJECT_NAME_M4`' is a `'M4_PROJECT_DESCRIPTION`'.

.. note::
	In case you find errors in this documentation you can help by sending
	`pull requests <https://github.com/libuv/`'M4_LPROJECT_NAME_M4`'>`_!

Features
--------
* Cross platform
* Flexible command line options

Documentation
-------------

.. toctree::
	:maxdepth: 1

	design
	tutorial
	guide
	api

Obtaining
---------
'`M4_LPROJECT_NAME_M4`' binaries can be downloaded `here <http://github.com/user/`'M4_LPROJECT_NAME_M4`'/releases>`_.

To install from source, follow the instructions in the `README <https://github.com/libuv/`'M4_LPROJECT_NAME_M4`'/blob/master/README.md>`_.
