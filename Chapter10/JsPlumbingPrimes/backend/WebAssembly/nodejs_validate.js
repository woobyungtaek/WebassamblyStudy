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

Module['onRuntimeInitialized']= function() {
    let errorMessage = "";
    const errorMessagePointer = Module._malloc(256); // 모듈 메모리 확보 256바이트

    if (!validateName(clientData.name, errorMessagePointer) ||
        !validateCategory(clientData.categoryId, errorMessagePointer))
    {
        errorMessage = Module.UTF8ToString(errorMessagePointer);
    }

    Module._free(errorMessagePointer);

    setErrorMessage(errorMessage);
    if (errorMessage === "") {}
}

function validateName(name, errorMessagePointer) {
    const isValid = Module.ccall(
        'ValidateName', //호출하려는 모듈 함수명
        'number', //함수 반환형
        ['string', 'number', 'number'], // 매개변수 자료형 배열
        [name, MAXIMUM_NAME_LENGTH, errorMessagePointer] //매개변수 값 배열
    );

    return (isValid === 1);
}

function validateCategory(categoryId, errorMessagePointer) {
    const arrayLength = VALID_CATEGORY_IDS.length;
    const bytesPerElement = Module.HEAP32.BYTES_PER_ELEMENT;
    const arrayPointer = Module._malloc((arrayLength * bytesPerElement));
    Module.HEAP32.set(VALID_CATEGORY_IDS, (arrayPointer / bytesPerElement));

    const isValid = Module.ccall(
        'ValidateCategory',
        ['string', 'number', 'number', 'number'],
        [categoryId, arrayPointer, arrayLength, errorMessagePointer]
    );

    Module._free(arrayPointer);

    return (isValid === 1);
}