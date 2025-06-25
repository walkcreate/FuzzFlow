#!/usr/bin/env node

import fs from "fs";
import path from "path";
import { fileURLToPath } from "url";
import { transformFile } from "./transformer/transformer.js";
import { program } from "commander";

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

async function processFile(inputFile, outputFile) {
    try {
        const code = fs.readFileSync(inputFile, "utf-8");
        const transformed = await transformFile(code);

        if (transformed === null) {
            console.warn(`⚠️  Skipped (transform error): ${inputFile}`);
            return;
        }

        fs.mkdirSync(path.dirname(outputFile), { recursive: true });
        fs.writeFileSync(outputFile, transformed);
        console.log(`✅ Transformed: ${inputFile} → ${outputFile}`);
    } catch (err) {
        console.warn(`⚠️  Failed to process: ${inputFile} → ${err.message}`);
    }
}

async function processDirectory(inputDir, outputDir) {
    const entries = fs.readdirSync(inputDir, { withFileTypes: true });

    for (const entry of entries) {
        const inputEntryPath = path.join(inputDir, entry.name);
        const outputEntryPath = path.join(outputDir, entry.name);

        if (entry.isDirectory()) {
            await processDirectory(inputEntryPath, outputEntryPath);
        } else if (entry.isFile() && entry.name.endsWith(".js")) {
            await processFile(inputEntryPath, outputEntryPath);
        }
    }
}

program
    .name("js-transformer")
    .description("Standardize and desugar JavaScript code using Babel")
    .option("-i, --input <path>", "Input file or directory path")
    .option("-o, --output <path>", "Output file or directory path (optional)");

program.parse(process.argv);

const options = program.opts();

if (!options.input) {
    console.error("❌ Error: Input path is required.");
    process.exit(1);
}

const inputPath = path.resolve(options.input);
const outputPath = options.output ? path.resolve(options.output) : null;


if (fs.lstatSync(inputPath).isFile()) {
    const outFile = outputPath || inputPath.replace(/\.js$/, ".transformed.js");
    processFile(inputPath, outFile);
}
else if (fs.lstatSync(inputPath).isDirectory()) {
    if (!outputPath) {
        console.error("❌ Error: Output directory required when processing a directory.");
        process.exit(1);
    }

    fs.mkdirSync(outputPath, { recursive: true });

    await processDirectory(inputPath, outputPath);
}
else {
    console.error("❌ Error: Invalid input path.");
    process.exit(1);
}
