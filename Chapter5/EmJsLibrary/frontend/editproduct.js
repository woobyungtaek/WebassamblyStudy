
const MAXIMUM_NAME_LENGTH = 50;
const VALID_CATEGORY_IDS = [100, 101];

const initialData = {
    name: "Women's Mid Rise Skinny Jeans",
    categoryId: "100",
}

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
    setErrorMessage("");

    const name = document.getElementById("name").value;
    const categoryId = getSelectedCategoryId();

    if (validateName(name) && validateCategory(categoryId))
    {

    }
}

function validateName(name) {
    const isValid = Module.ccall(
        'ValidateName', //호출하려는 모듈 함수명
        'number', //함수 반환형
        ['string', 'number'], // 매개변수 자료형 배열
        [name, MAXIMUM_NAME_LENGTH] //매개변수 값 배열
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