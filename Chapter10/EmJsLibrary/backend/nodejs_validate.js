
const MAXIMUM_NAME_LENGTH = 50;
const VALID_CATEGORY_IDS = [100, 101];

const clientData = {
    name: "asdfasdfasdfsdafsadfsadf",
    categoryId: "100",
}

global.setErrorMessage = function (error) {
    console.log(error);
}

const Module = require('./validate.js');

Module['onRuntimeInitialized'] = function ()
{
    if (validateName(clientData.name) && validateCategory(clientData.categoryId))
    {

    }
}

function validateName(name) {
    const isValid = Module.ccall(
        'ValidateName', //ȣ���Ϸ��� ��� �Լ���
        'number', //�Լ� ��ȯ��
        ['string', 'number'], // �Ű����� �ڷ��� �迭
        [name, MAXIMUM_NAME_LENGTH] //�Ű����� �� �迭
    );

    return (isValid === 1);
}

function validateCategory(categoryId) {
    const arrayLength = VALID_CATEGORY_IDS.length;
    const bytesPerElement = Module.HEAP32.BYTES_PER_ELEMENT;
    const arrayPointer = Module._malloc((arrayLength * bytesPerElement));
    Module.HEAP32.set(VALID_CATEGORY_IDS, (arrayPointer / bytesPerElement));

    const isValid = Module.ccall(
        'ValidateCategory',
        ['string', 'number', 'number'],
        [categoryId, arrayPointer, arrayLength]
    );

    Module._free(arrayPointer);
    return (isValid === 1);
}