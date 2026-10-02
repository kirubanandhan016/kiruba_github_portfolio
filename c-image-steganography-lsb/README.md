# Image Steganography in C

A command-line C implementation that hides and extracts a text message in 24-bit uncompressed BMP images using least-significant-bit (LSB) encoding.

## Features
- BMP signature validation
- 24-bit uncompressed BMP support
- Capacity checking
- LSB encoding
- LSB decoding
- File and argument validation
- Error reporting

## Build
```bash
make
```

## Usage
Encode:
```bash
./steg encode input.bmp output.bmp "hello"
```

Decode:
```bash
./steg decode output.bmp
```

## Validation
The implementation checks:
- Missing files
- Invalid BMP signature
- Unsupported bit depth/compression
- Insufficient capacity
- Empty messages
- Invalid command-line arguments

This project performs software validation only; it does not claim security-grade cryptographic steganography.
