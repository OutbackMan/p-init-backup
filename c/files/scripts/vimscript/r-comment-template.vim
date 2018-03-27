
function! g:r_comment_template_handler()
	let l:uproject_name
	let l:lproject_name
	let l:project_description
	let l:git_user_name
	let l:git_user_email

	" Parse the project_name_file to retrieve the date
	let l:year_of_creation

	let l:r_comment_template = '\
	\/*******************************************************************************
	\
	\Copyright (C) `'YEAR_OF_CREATION`', `'M4_GIT_USER_NAME_M4`' <`'M4_GIT_USER_EMAIL_M4`'>
	\
	\src/`'M4_LPROJECT_NAME_M4`'.c: 
	\	<+INSERT-FILE-DESCRIPTION+>
	\
	\`'M4_UPROJECT_NAME_M4`':
	\	"`'M4_PROJECT_DESCRIPTION_M4`'"
	\
	\License:
	\	"This file is subject to the terms and conditions defined in
	\	'LICENSE.md', which is part of this source code package."
	\
	\*******************************************************************************/'

endfunction

autocmd BufNewFile *.c,h silent! 0r templates/c/r-comment-template.tpl
