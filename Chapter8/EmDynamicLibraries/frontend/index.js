
const MAXIMUM_NAME_LENGTH = 50;
const VALID_CATEGORY_IDS = [100, 101];
const VALID_PRODUCT_IDS = [200, 301];

let productModule = null;
let orderModule = null;

const initialProductData = {
    name: "Women's Mid Rise Skinny Jeans",
    categoryId: "100",
}


function initializePage() {
    document.getElementById("name").value = initialProductData.name;

    const category = document.getElementById("category");
    const count = category.length;
    for (let index = 0; index < count; index++) {
        if (category[index].value === initialProductData.categoryId) {
            category.selectedIndex = index;
            break;
        }
    }

    let showEditProduct = true;
    if ((window.location.hash) && (window.location.hash.toLocaleLowerCase() === "#placeorder")) {
        showEditProduct = false;
    }
    switchForm(showEditProduct);
}

function switchForm(showEditProduct) {
    setErrorMessage("");
    setActiveNavLink(showEditProduct);
    setFormTitle(showEditProduct);

    if (showEditProduct) {
        if (productModule === null) {
            productModule = new Module({ dynamicLibraries: ['validate_product.wasm'] });
        }
        showElement("productForm", true);
        showElement("orderForm", false);
    }
    else {
        if (orderModule === null) {
            orderModule = new Module({ dynamicLibraries: ['validate_order.wasm'] });
        }
        showElement("productForm", false);
        showElement("orderForm", true);
    }
}

function setActiveNavLink(editProduct) {
    const navEditProduct = document.getElementById("navEditProduct");
    const navPlaceOrder = document.getElementById("navPlaceOrder");

    navEditProduct.classList.remove("active");
    navPlaceOrder.classList.remove("active");

    if (editProduct) { navEditProduct.classList.add("active"); }
    else { navPlaceOrder.classList.add("active"); }
}

function setFormTitle(editProduct) {
    const title = (editProduct ? "Edit Product" : "Place Order");
    document.getElementById("formTitle").innerText = title;
}

function showElement(elementId, show) {
    const element = document.getElementById(elementId);
    element.style.display = (show ? "" : "none");
}




function getSelectedDropdownId(elementId) {
    const dropdown = document.getElementById(elementId);
    const index = dropdown.selectedIndex;
    if (index != -1) { return dropdown[index].value; }
    return 0;
}

function setErrorMessage(error) {
    const errorMessage = document.getElementById("errorMessage");
    errorMessage.innerText = error;
    showElement("errorMessage", (error !== ""));
}

function onClickSaveProduct() {
    setErrorMessage("");

    const name = document.getElementById("name").value;
    const categoryId = getSelectedDropdownId("category");

    if (validateName(name) && validateCategory(categoryId)) { }
}


function validateName(name) {

    const isValid = productModule.ccall(
        'ValidateName', //호출하려는 모듈 함수명
        null, //함수 반환형
        ['string', 'number'], // 매개변수 자료형 배열
        [name, MAXIMUM_NAME_LENGTH] //매개변수 값 배열
    );
}

function validateCategory(categoryId) {

    const arrayLength = VALID_CATEGORY_IDS.length;
    const bytesPerElement = Module.HEAP32.BYTES_PER_ELEMENT;
    const arrayPointer = productModule._malloc((arrayLength * bytesPerElement));
    productModule.HEAP32.set(VALID_CATEGORY_IDS, (arrayPointer / bytesPerElement));

    const isValid = productModule.ccall(
        'ValidateCategory',
        ['string', 'number', 'number'],
        [categoryId, arrayPointer, arrayLength]
    );

    productModule._free(arrayPointer);

    return (isValid === 1);
}


function OnClickAddToCart() {
    setErrorMessage("");

    const productId = getSelectedDropdownId("product");
    const quantity = document.getElementById("quantity").value;

    if (validateProduct(productId) && validateQuantity(quantity)) { }
}

function validateProduct(productId) {
    const arrayLength = VALID_PRODUCT_IDS.length;
    const bytesPerElement = orderModule.HEAP32.BYTES_PER_ELEMENT;
    const arrayPointer = orderModule._malloc((arrayLength * bytesPerElement));
    orderModule.HEAP32.set(VALID_PRODUCT_IDS, (arrayPointer / bytesPerElement));

    const isValid = orderModule.ccall(
        'ValidateProduct'
        ['string', 'number', 'number'],
        [productId, arrayPointer, arrayLength]
    );

    orderModule._free(arrayPointer);
    return (isValid === 1);
}

function validateQuantity(quantity) {
    const isValid = orderModule.ccall(
        'ValidateQuantity',
        'number',
        ['string'],
        ['quantity']
    );

    return (isValid === 1);
}
