function logPrime(prime) {
    console.log(prime.toString());
}

function initializePage() {

    const isPrimeImportObject = {
        env: {
            memory: new WebAssembly.Memory({ initial: 0 }),
            table: new WebAssembly.Table({ initial: 2, element: "anyfunc" }),
            __memory_base: 0,
            __table_base: 0,
        }
    };

    WebAssembly.instantiateStreaming(fetch("is_prime.wasm"), isPrimeImportObject).then(module => {
        const findPrimesImportObject = {
            env: {
                memory: new WebAssembly.Memory({ initial: 0 }),
                table: new WebAssembly.Table({ initial: 2, element: "anyfunc" }),
                __memory_base: 0,
                __table_base: 0,
                IsPrime: module.instance.exports.IsPrime,
                LogPrime: logPrime,
            }
        };

        return WebAssembly.instantiateStreaming(fetch("find_primes.wasm"), findPrimesImportObject);
    }).then(module => { module.instance.exports.FindPrimes(3, 100); });
}