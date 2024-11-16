# Spit

Spit is a simple command-line shell for Windows, inspired by the tutorial [Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/) by **Stephen Brennan**. I wanted to get familiar with the Windows API so I adjusted some of the functions, and I added some more functions.

## Installation

To install and set up the project, follow these steps:

```bash
# Clone the repository
git clone https://github.com/yourusername/Spit.git

# Navigate to the project directory
cd Spit

# Build the project using gcc
gcc -o spit src/main.c src/lib/lib.c
```

## Usage

To use the project, run the following command:

```bash
# Run the project
./spit
```

## Contributing

Guidelines for contributing to the project:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes.
4. Commit your changes (`git commit -m 'Add some feature'`).
5. Push to the branch (`git push origin feature-branch`).
6. Open a pull request.

## License

This project is licensed under the Unlicense - see the [LICENSE](LICENSE) file for details.

## Acknowledgements

- Special thanks to Mats Erik Andersson for creating lsh.
- Special thanks to Stephen Brennan for his tutorial on writing a shell in C.