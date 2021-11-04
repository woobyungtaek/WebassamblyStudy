let compiledModule = null;
let emscriptenModule = null;

//昆 况目 积己
const worker = new Worker("prefetch.worker.js");
worker.onmessage = function (e) {
    compiledModule = e.data;

    emscriptenModule = new Module({ instantiateWasm: onInstantiateWasm });
}

function onInstantiateWasm(importObject, successCallBack) {
    WebAssembly.instantiate(compiledModule, importObject).then(instance => successCallBack(instance));

    return {};
}