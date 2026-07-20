const core = require('@actions/core');
const fs = require('fs');
const path = require('path');

try {
    const elfFile = core.getInput('elf-file', { required: true });
    const mcu = core.getInput('mcu', { required: true });
    const buildType = core.getInput('build-type', { required: true });

    const resolvedPath = path.resolve(elfFile);

    core.info(`MCU: ${mcu}`);
    core.info(`Build type: ${buildType}`);
    core.info(`ELF file: ${resolvedPath}`);

    if (!fs.existsSync(resolvedPath)) {
        throw new Error(`ELF file does not exist: ${resolvedPath}`);
    }

    const stats = fs.statSync(resolvedPath);

    if (!stats.isFile()) {
        throw new Error(`Path is not a file: ${resolvedPath}`);
    }

    core.info(`ELF file size: ${stats.size} bytes`);

    core.setOutput('file-size', stats.size.toString());
} catch (error) {
    core.setFailed(error instanceof Error ? error.message : String(error));
}