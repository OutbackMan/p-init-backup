# CONTRIBUTING

`'M4_LPROJECT_NAME_M4` welcomes new contributors. This document will guide you
through the process.
Please make sure you have read the [README.md](README.md) file before you proceed.

## FORK

Fork the project [on GitHub](https://github.com/libuv/libuv) and check out
your copy.

``` bash
$ # clone the repository:
$ git clone https://github.com/username/libuv.git
$ # move to `'M4_LPROJECT_NAME_M4`' directory:
$ cd `'M4_LPROJECT_NAME_M4`'
$ # add `'M4_LPROJECT_NAME_M4`' remote:
$ git remote add upstream https://github.com/libuv/libuv.git
```

`'M4_LPROJECT_NAME_M4`' uses the [gitflow](link) workflow. 
With this in mind, decide on the appropriate branch for your work to go into. 

NOTE: Any patches that change `'M4_LPROJECT_NAME_M4`''s API will get rejected.

In case of doubt, post your question on [gitter](link). 

Especially do so if you plan to work on something big. Nothing is more
frustrating than seeing your hard work go to waste because your vision
does not align with that of a project maintainers.

### BRANCH

```bash
$ # create appropriate branch
$ git checkout -b <my-branch-name> -t origin/<`'M4_LPROJECT_NAME_M4`'-branch-name>
```

### CODE

Use gnu indent as linter ???
Please adhere to [`'M4_LPROJECT_NAME_M4`''s code style](CODE-STYLE.md). 

### COMMIT

Make sure git knows your name and email address:

```bash
$ # configure username
$ git config --global user.name <user-name>
$ # configure user email
$ git config --global user.email <user-email>
```

Writing good commit logs is important.  A commit log should describe what
changed and why.  Follow these guidelines when writing one:

1. The first line should be 50 characters or less and contain a short
   description of the change prefixed with the name of the changed
   subsystem (e.g. "utils/misc: add want_config to `'M4_UPROJECT_NAME_M4`'_Args").
2. Keep the second line blank.
3. Wrap all other lines at 72 columns.

A good commit log looks like this:

```
subsystem: explaining the commit in one line

Body of commit message is a few lines of text, explaining things
in more detail, possibly giving some background about the issue
being fixed, etc etc.

The body of the commit message can be several paragraphs, and
please do proper word-wrap and keep columns shorter than about
72 characters or so. That way `git log` will show things
nicely even when it is indented.
```

The header line should be meaningful; it is what other people see when they
run `git log --oneline`.

Check the output of `git log --oneline files_that_you_changed` to find out
what subsystem(s) your changes touch.

### REBASE

Use `git rebase` (not `git merge`) to sync your work from time to time.

```
$ git fetch upstream
$ git rebase upstream/<`'M4_LPROJECT_NAME_M4`'-branch-name>
```

### TEST

All significant changes should come with tests.  Add your tests in the
`test/` directory. If you add a new test file, it needs to be registered in `Makefile.am` by adding the file's name to the `test_run_tests_SOURCES` list.

Look at other tests to see how they should be structured and to make sure that there are no test regressions.

### PUSH

```
$ git push origin <my-branch-name>
```

Go to https://github.com/username/libuv and select your feature branch.  Click
the 'Pull Request' button and fill out the form.

Pull requests are usually reviewed within a few days.  If there are comments
to address, apply your changes in a separate commit and push that to your
feature branch.  Post a comment in the pull request afterwards; GitHub does
not send out notifications when you add commits.
