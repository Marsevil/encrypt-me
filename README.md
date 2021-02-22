# encrypt-me

## Description

This app have to maintain coherence between 2 files hierarchy which are both copy of each other but in two different directories. Moreover, one of these is encrypted, not the other.

## Installation

- Clone repository.
- `cd encrypt-me`.
- `cmake -B build`.
- `cd build`.
- `make`.
- `mv lyoko path/to/wherever/you/want`.

## Dependencies

- openssl
- doxygen (for documentation)

## Build dependencies

- cmake
- gcc
- make

## How to use

### Setup

- Create a new file ~/encrypt-me_config.env
- Put each property following `<property name> = <property value> <return>`
    - *PASSWORD* configure password use to encrypt and decrypt
    - *UNCRYPTED_FOLDER* path to the clear version of your directory
    - *ENCRYPTED_FOLDER* path to the encrypted version of your directory
    
```
PASSWORD = thisIsASecuredPassword
UNCRYPTED_FOLDER = /path/to/your/folder/where/files/are/readable
ENCRYPTED_FOLDER = /path/to/your/folder/where/files/are/not/readable
```
> Exemple of encrypt-me_config file.

### Commands

- `lyoko --help` or `lyoko -h` show help page
- `lyoko push` encrypt all files from clear directory to encrypted
- `lyoko pull` decrypt all files from encrypted directory to clear
- adding `diff` parameter only display change without applying
- adding `--verbose` or `-v` option show each step of the execution
- adding `--ask-confirm` option will display all changes before applying
 
## Generate documentation

- `doxygen`.