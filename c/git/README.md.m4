# `'M4_LPROJECT_NAME_M4`':
![Screenshot previewing `'M4_LPROJECT_NAME_M4`'](img/`'M4_LPROJECT_NAME_M4`'_preview_screenshot.png "Preview of `'M4_LPROJECT_NAME_M4`'")

## Overview
`'M4_LPROJECT_DESCRIPTION`' is a `'M4_PROJECT_DESCRIPTION_M4`'.

## Feature Highlights
	* Cross platform
	* Flexible command line argument handling 

## Versioning
`'M4_LPROJECT_NAME_M4`' follows the [semantic](https://semver.org/) versioning scheme.

## Licensing
`'M4_LPROJECT_NAME_M4`' is licensed under the MIT license. Check the [LICENSE.md file](LICENSE.md).
The documentation for `'M4_LPROJECT_NAME_M4`' is licensed under the Creative Commons Attribution 4.0 International license. Check the [LICENSE-docs.md file](LICENSE-docs.md).

## Support
For generic questions about `'M4_LPROJECT_NAME_M4`' you are encouraged to engage with the `'M4_LPROJECT_NAME_M4`' community on [gitter](link)

## Documentation
The documentation for `'M4_LPROJECT_NAME_M4`' is located in the `docs/` subdirectory. It uses the [Sphinx](http://sphinx-doc.org/)
framework, which makes it possible to build the documentation in multiple formats.

```bash
$ # navigate to the location of `'M4_LPROJECT_NAME_M4`''s documentation:
$ cd docs/
$ # show supported documentation building options:
$ make help
$ # e.g build documentation as HTML:
$ make html
```

Documentation can also be browsed online [here](http://docs.libuv.org).

## Downloading

### Binary
Download the appropriate binaries for your OS from `'M4_LPROJECT_NAME_M4`' [releases page](release link):
[Linux](project release link)
[Windows](project release link)
[Mac](project release link)

### Source
#### Prerequisites
##### Programs 

| Linux/Mac               | Windows |
| :---------------------: | :-----: |
| git, gpg, GNU autotools, gcc | msys2   |

##### Libraries

* libcheck (C unit testing framework)

#### Verifying
All `'M4_LPROJECT_NAME_M4`' release tags are signed with the developer's key.
The relevent GPG key(s) to import are listed in the [MAINTAINERS.md](link) file.

```bash
$ # import gpg key:
$ gpg --keyserver pool.sks-keyservers.net --recv-keys <gpg-key>
$ # verify release tag:
$ git verify-tag <tag-name>
```
#### Obtain 
```bash
$ # clone the repository:
$ git clone (link)  
$ # navigate to `'M4_LPROJECT_NAME_M4`' project directory:
$ cd `'M4_LPROJECT_NAME_M4`'/
$ # prepare for `'M4_LPROJECT_NAME_M4`' build compilation: 
$ sh autogen.sh
$ # list possible configure options for `'M4_LPROJECT_NAME_M4`':
$ ./configure --help
$ # e.g, generate a `'M4_LPROJECT_NAME_M4`' release mode makefile:
$ ./configure --enable-release
$ # generate `'M4_LPROJECT_NAME_M4`'' binary
$ make
$ # run `'M4_LPROJECT_NAME_M4`''s test suite:
$ make check
$ # list possible arguments for `'M4_LPROJECT_NAME_M4`' binary:
$ ./`'M4_LPROJECT_NAME_M4`' --help
$ # e.g, run `'M4_LPROJECT_NAME_M4`' binary with verbose enabled:
$ ./`'M4_LPROJECT_NAME_M4`' --verbose

```

## Contributing
To obtain the guidelines for contributing to `'M4_LPROJECT_NAME_M4`', please refer to the [contributing file](CONTRIBUTING.md).



windows:
msys2 (x86_64) (install instructions)
(if already installed: pacman -Syuu; then pacman -S base-devel mingw-w64-x86_64-toolchain git)
(then open msys2 mingw 64-bit shell; can use gcc, make, autoreconf, etc.)
(pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-check)

-lmingw32 -lSDL2main -lSDL2 (this order is necessary as gcc only resolves undefined symbols. needed for WinMain)
