
# String Encoder in C Language

This project provides a simple implementation of a string encoder in the C programming language. The program includes three encoding techniques: Base64 encoding, XOR encoding, and Caesar encoding.

<img src="https://img.wonderhowto.com/img/58/39/63564100393350/0/hack-like-pro-cryptography-basics-for-aspiring-hacker.1280x600.jpg">

### Base64 Encoding

The encode_base64 function takes a user-provided string as input and returns the Base64 encoded version of the string. The function follows the standard Base64 encoding algorithm. The decode_base64 function decodes a Base64 encoded string back to its original form.



### XOR Encoding
The encode_xor function performs XOR encoding on the user-provided string using a key. Each character of the input string is XORed with the corresponding character of the key. The decode_xor function performs the same XOR operation, effectively decrypting the encoded string.

### Caesar Encoding
The encode_caesar function implements Caesar encoding, which involves shifting each character of the user-provided string by a given number of positions. The shift value determines the encryption key. The decode_caesar function reverses the shift operation, decrypting the encoded string.

### Usage

When you run the program, you will be prompted to choose an encoding technique: base64, xor, or caesar.
Enter the desired string that you want to encode.
For base64 and xor encoding, additional inputs (key or shift) will be requested.
The program will display the encoded string and the decoded string, if applicable.


## Authors

- [@soheil-vanaee](https://www.github.com/soheil-vanaee)


## Installation



```bash
  git clone https://github.com/soheil-vanaee/String-Encoder-in-C-Language.git
  cd String-Encoder-in-C-Language
  gcc main.c 
  ./a.out
```
    
