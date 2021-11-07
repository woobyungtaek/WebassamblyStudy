const fs = require('fs');

fs.readFile('side_module.wasm', function (error, byte) {
    if (error) { throw error; }

    instantiateWebAssembly(byte);
});

function instantiateWebAssembly(bytes) {
    const importObject = {
        env: {
            __memory_base: 0,
            __table_base: 0,
            'memory': new WebAssembly.Memory({ initial: 256 }),
            'table': new WebAssembly.Table({ initial: 256, element: 'anyfunc' }),
        }
    };

    WebAssembly.instantiate(bytes, importObject).then(result => {
        const value = result.instance.exports.Increment(2);
        console.log(value.toString());
    });
}