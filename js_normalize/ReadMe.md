
# JS Normalize & Desugar

A Babel-based JavaScript transformation project that standardizes code and removes modern syntactic sugar to produce simplified, traditional JavaScript.

## Features

The project includes two categories of transformation plugins:

### 1. **Normalization Plugins**

Standardize JavaScript code by applying transformations such as:

- Removing comments (`comment.js`)
- Expanding comma expressions (`expand-comma-expression.js`)
- Converting function expressions to declarations (`function-expression.js`)
- Hoisting variable declarations (`hoisting.js`)
- *...and more*

### 2. **Desugaring Plugins**

Remove modern JavaScript syntactic sugar by transforming:

- Arrow functions → regular functions  
- `class` declarations → function constructors + property assignments  
- Destructuring assignments → standard assignments  
- `for...in` loops → standard `for` loops  
- `for...of` loops → standard `for` loops  
- *...and more*

## Installation

Before running the tool, make sure to install dependencies:
```bash
npm install
```

## Usage

```bash
node ./main.js -i <input_file_or_directory> -o <output_file_or_directory>
```

Examples

- Transform a single file:
```bash
node ./main.js -i ./input/example.js -o ./output/example.js
```

- Transform all .js files in a directory (recursive):
```bash
node ./main.js -i ./input_dir -o ./output_dir
```