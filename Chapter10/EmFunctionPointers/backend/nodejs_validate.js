
const MAXIMUM_NAME_LENGTH = 50;
const VALID_CATEGORY_IDS = [100, 101];

const clientData = {
    name: "Women's Mid Rise Skinny Jeans",
    categoryId: "100",
}

function setErrorMessage(error) {
    console.log(error);
}

const Module = require('./validate.js');

Module['onRuntimeInitialized'] = function () {
    Promise.all([validateName(clientData.name), validateCategory(clientData.categoryId)]).then(() => {}).catch((error) => { setErrorMessage(error); });
}

function validateName(name) {

    return new Promise(function (resolve, reject) {
        const pointers = { onSuccess: null, onError: null };
        createPointers(resolve, reject, pointers);

        Module.ccall(
            'ValidateName', //호출하려는 모듈 함수명
            null, //함수 반환형
            ['string', 'number', 'number', 'number'], // 매개변수 자료형 배열
            [name, MAXIMUM_NAME_LENGTH, pointers.onSuccess, pointers.onError] //매개변수 값 배열
        );
    });
}

function validateCategory(categoryId) {
    return new Promise(function (resolve, reject) {
        const pointers = { onSuccess: null, onError: null };
        createPointers(resolve, resject, pointers);

        const arrayLength = VALID_CATEGORY_IDS.length;
        const bytesPerElement = Module.HEAP32.BYTES_PER_ELEMENT;
        const arrayPointer = Module._malloc((arrayLength * bytesPerElement));
        Module.HEAP32.set(VALID_CATEGORY_IDS, (arrayPointer / bytesPerElement));

        Module.ccall(
            'ValidateCategory',
            ['string', 'number', 'number', 'number', 'number'],
            [categoryId, arrayPointer, arrayLength, pointers.onSuccess, pointers.onError]
        );

        Module._free(arrayPointer);
    });
}

function createPointers(resolve, reject, returnPointers) {

    const onSuccess = Module.addFunction(function () { freePointers(onSuccess, onError); resolve(); }, 'v');

    const onError = Module.addFunction(function (errorMessage) { freePointers(onSuccess, onError); reject(Module.UTF8ToString(errorMessage)); }, 'vi');

    returnPointers.onSuccess = onSuccess;
    returnPointers.onError = onError;
}

function freePointers(onSuccess, onError) {
    Module.removeFunction(onSuccess);
    Module.removeFunction(onError);
}
