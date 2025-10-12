# Image encryptor/decryptor

**Table of Contents:**
***
- [What is this](#what-is-this)
  - [Cipher](#cipher)
  - [Filetypes](#filetypes)
  - [Args](#args)
  - [Installation](#installation)
    - [Direct](#direct)
    - [Manual](#manual)
  - [Usage](#usage)
***
## What is this
Program for encrypting and decrypting images. It uses Vernam's cipher for encrypting all pixels
> NOTE
> This program encrypts PIXEL DATA only, not the complete image file. The main idea was to see the encrypted image, therefore the original file structure, metadata, and compression may be altered during the process. While decrypted images will display identical visual content, file size and hashes may differ from the original.


## Cipher
The program uses [Vernam's cipher](https://en.wikipedia.org/w/index.php?title=Gilbert_Vernam&section=3#The_Vernam_cipher) to encrypt image pixels through XOR operations with a password key. This provides theoretical unbreakability when used with a truly random key of sufficient length.

## Filetypes
| Encryption | Decryption | :fa-check:/:fa-times: | 
| :--------------: | :--------------:| :-----------: |
| png/bmp -> png/bmp | png/bmp -> png/bmp | :fa-check: |
| jpeg -> png/bmp | png/bmp -> png/bmp | :fa-check: |
| jpeg -> png/bmp/jpeg | png/bmp/jpeg -> jpeg | :fa-times: |

>    JPEG format uses lossy compression which can distort encrypted/decrypted images during saving.

## Args

All args that program supports, you can also see them with -h/--help

```sh
Allowed options:
  -h [ --help ]               Show this help message and exit
  -i [ --input-image ] arg    Input image file path
  -o [ --output-image ] arg   Output image file path
  -p [ --password ] arg       Use provided text as password
  -g [ --password-generate ]  Generate a random password automatically
  -f [ --password-from ] arg  Read password from specified file
  ```

## Installation
### Direct
You can install binary file directly from the [releases page](https://github.com/notseriouss/ImagEncrypt/releases)

### Manual
You will need to have OpenCV installed
```sh
git clone https://github.com/notseriouss/ImageEncrypt.git image_encryptor
cd image_encryptor
mkdir build && cd build
cmake .. && make
```
## Usage
Usage is actually very simple:
1. Basically all you need to do is to pass the input image which you want to encrypt by using
`--input-image=/path/to/image.png  or  -i path/to/image.png`

2. And provide the output path for encrypted image where you want to save it  using
`--output-image=/path/to/image.png   or  -o path/to/image.png `

3.  Then password, the program has 3 options for working with passwords:
* You can pass your password just by providing it to the program using 
`--password=your password`

* You can generate random password with the length of all image pixels using
`--password-generate `
> program saves your password as password.txt in the same dir where it was executed

* You can import your password from .txt file using
`--password-from=/path/to/password.txt`
