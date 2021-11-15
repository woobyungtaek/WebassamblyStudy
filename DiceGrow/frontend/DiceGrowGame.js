const FORM_NAMES = [
    "LoginForm",
    "SignUpForm",
    "PlayerStateForm",
    "RollDiceForm",
    "BattleReadyForm",
    "BattleForm"
];

var currentTurn;

// ������ �ε� �� �ʱ�ȭ
function initializePage() {
    console.log("���� �ʱ�ȭ");
    AllFormNoShow();
    showElement("LoginForm", true);
}

// ����� display ���¸� �����Ѵ�.
function showElement(elementId, show) {
    const element = document.getElementById(elementId);
    element.style.display = (show ? "" : "none");
}

// ��� Form ����
function AllFormNoShow() {

    const arrayLength = FORM_NAMES.length;

    for (var formIdx = 0; formIdx < arrayLength; ++formIdx) {
        showElement(FORM_NAMES[formIdx], false);
    }
}


//-------------------------
//       �α��� Form
//-------------------------

// �α��� ��ư Ŭ��
function OnClicked_LoginButton() {
    AllFormNoShow();
    showElement("PlayerStateForm", true);
}

// ȸ�� ���� ��ư Ŭ��
function OnClicked_SignUpButton() {
    AllFormNoShow();
    showElement("SignUpForm", true);
}


//-------------------------
//     ȸ�� ���� Form
//-------------------------

// ���ư��� ��ư
function OnClicked_BackButton() {
    AllFormNoShow();
    showElement("LoginForm", true);
}


//-------------------------
//   �÷��̾� ���� Form
//-------------------------

// HP ����
function RefreshHpUI() {
}

// �ֻ��� ����
function RefreshDiceSlotUI(slotNum) {

}

// �����ϱ� ��ư
function OnClicked_GoButton() {
    AllFormNoShow();
    showElement("RollDiceForm", true);
}

// ���� �� ������ ��ư
function OnClicked_SaveAndExitButton() {
    AllFormNoShow();
    showElement("LoginForm", true);

}


//-------------------------
//     �ֻ��� ������ Form
//-------------------------

// �ֻ��� ������ ��ư
function OnClicked_RollDiceButton() {
    AllFormNoShow();
    showElement("BattleReadyForm", true);
}


//-------------------------
//     ���� �غ� Form
//-------------------------

// ���� ���� ��ư 
function OnClicked_BattleStartButton() {
    currentTurn = 0;

    AllFormNoShow();
    showElement("BattleForm", true);
}

//-------------------------
//     ���� Form
//-------------------------

// ���� �� ��ư
function OnClicked_NextTurnButton() {
    currentTurn += 1;
    console.log("CurrentTurn : " + currentTurn);
}

// ���� ���� ��ư
function OnClicked_NextRoundButton() {
    AllFormNoShow();
    showElement("RollDiceForm", true);
}

// ���� ���� ��ư
function OnClicked_BattleEndButton() {
    AllFormNoShow();
    showElement("PlayerStateForm", true);
}