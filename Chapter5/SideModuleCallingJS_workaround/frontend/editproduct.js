
const MAXIMUM_NAME_LENGTH = 50;
const VALID_CATEGORY_IDS = [100, 101];

const initialData = {
    name: "Women's Mid Rise Skinny Jeans",
    categoryId: "100",
}

let moduleMemory = null;
let moduleExports = null;

function initializePage() {
    document.getElementById("name").value = initialData.name;

    const category = document.getElementById("category");
    const count = category.length;
    for (let index = 0; index < count; index++) {
        if (category[index].value === initialData.categoryId) {
            category.selectedIndex = index;
            break;
        }
    }

    const importObject = {
        env: {
            _UpdateHostAboutError: function (errorMessagePointer) { setErrorMessage(getStringFromMemory(errorMessagePointer)); }
        }
    };

    // 모듈을 다운로드/인스턴스화 한다.
    WebAssembly.instantiateStreaming(fetch("validate.wasm"), importObject).then(result => {
        moduleExports = result.instance.exports;
        moduleMemory = moduleExports.memory;
    });
}

function getSelectedCategoryId() {
    const category = document.getElementById("category");
    const index = category.selectedIndex;
    if (index !== -1) { return category[index].value; }

    return 0;
}

function setErrorMessage(error) {
    const errorMessage = document.getElementById("errorMessage");
    errorMessage.innerText = error;
    errorMessage.style.display = (error === "" ? "none" : "");
}

function onClickSave() {
    let errorMessage = "";
    const errorMessagePointer = moduleExports.malloc(256); // 모듈 메모리 확보 256바이트

    const name = document.getElementById("name").value;
    const categoryId = getSelectedCategoryId();

    if (!validateName(name, errorMessagePointer) || !validateCategory(categoryId, errorMessagePointer)) {
        errorMessage = getStringFromMemory(errorMessagePointer);
    }

    moduleExports.free(errorMessagePointer);

    setErrorMessage(errorMessage);
    if (errorMessage === "") { }
}

function validateName(name) {
    const namePointer = moduleExports.malloc((name.length + 1));
    copyStringToMemory(name, namePointer);

    const isValid = moduleExports.ValidateName(namePointer, MAXIMUM_NAME_LENGTH);

    moduleExports.free(namePointer);

    return (isValid === 1);
}

function validateCategory(categoryId) {
    const categoryIdPointer = moduleExports.malloc((categoryId.length + 1));
    copyStringToMemory(categoryId, categoryIdPointer);

    const arrayLength = VALID_CATEGORY_IDS.length;
    const bytesPerElement = Int32Array.BYTES_PER_ELEMENT;
    const arrayPointer = moduleExports.malloc((arrayLength * bytesPerElement));

    const bytesForArray = new Int32Array(moduleMemory.buffer);
    bytesForArray.set(VALID_CATEGORY_IDS, (arrayPointer / bytesPerElement));

    const isValid = moduleExports.ValidateCategory(categoryIdPointer, arrayPointer, arrayLength);

    moduleExports.free(arrayPointer);
    moduleExports.free(categoryIdPointer);

    return (isValid === 1);
}

function getStringFromMemory(memoryOffset) {
    let returnValue = "";

    const size = 256;
    const bytes = new Uint8Array(moduleMemory.buffer, memoryOffset, size);

    let character = "";
    for (let i = 0; i < size; i++) {
        character = String.fromCharCode(bytes[i]);
        if (character === "\0") { break; }

        returnValue += character;
    }

    return returnValue;
}

function copyStringToMemory(value, memoryOffset) {
    const bytes = new Uint8Array(moduleMemory.buffer);
    bytes.set(new TextEncoder().encode((value + "\0")), memoryOffset);
}