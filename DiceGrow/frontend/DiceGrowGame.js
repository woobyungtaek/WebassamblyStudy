const FORM_NAMES = [
    "LoginForm",
    "SignUpForm",
    "PlayerStateForm",
    "RollDiceForm",
    "BattleReadyForm",
    "BattleForm"
];

var currentTurn;

// 페이지 로드 시 초기화
function initializePage() {
    console.log("게임 초기화");
    AllFormNoShow();
    showElement("LoginForm", true);
}

// 요소의 display 상태를 변경한다.
function showElement(elementId, show) {
    const element = document.getElementById(elementId);
    element.style.display = (show ? "" : "none");
}

// 모든 Form 끄기
function AllFormNoShow() {

    const arrayLength = FORM_NAMES.length;

    for (var formIdx = 0; formIdx < arrayLength; ++formIdx) {
        showElement(FORM_NAMES[formIdx], false);
    }
}


//-------------------------
//       로그인 Form
//-------------------------

// 로그인 버튼 클릭
function OnClicked_LoginButton() {
    AllFormNoShow();
    showElement("PlayerStateForm", true);
}

// 회원 가입 버튼 클릭
function OnClicked_SignUpButton() {
    AllFormNoShow();
    showElement("SignUpForm", true);
}


//-------------------------
//     회원 가입 Form
//-------------------------

// 돌아가기 버튼
function OnClicked_BackButton() {
    AllFormNoShow();
    showElement("LoginForm", true);
}


//-------------------------
//   플레이어 정보 Form
//-------------------------

// HP 갱신
function RefreshHpUI() {
}

// 주사위 갱신
function RefreshDiceSlotUI(slotNum) {

}

// 진행하기 버튼
function OnClicked_GoButton() {
    AllFormNoShow();
    showElement("RollDiceForm", true);
}

// 저장 후 나가기 버튼
function OnClicked_SaveAndExitButton() {
    AllFormNoShow();
    showElement("LoginForm", true);

}


//-------------------------
//     주사위 굴리기 Form
//-------------------------

// 주사위 굴리기 버튼
function OnClicked_RollDiceButton() {
    AllFormNoShow();
    showElement("BattleReadyForm", true);
}


//-------------------------
//     전투 준비 Form
//-------------------------

// 전투 시작 버튼 
function OnClicked_BattleStartButton() {
    currentTurn = 0;

    AllFormNoShow();
    showElement("BattleForm", true);
}

//-------------------------
//     전투 Form
//-------------------------

// 다음 턴 버튼
function OnClicked_NextTurnButton() {
    currentTurn += 1;
    console.log("CurrentTurn : " + currentTurn);
}

// 다음 라운드 버튼
function OnClicked_NextRoundButton() {
    AllFormNoShow();
    showElement("RollDiceForm", true);
}

// 전투 종료 버튼
function OnClicked_BattleEndButton() {
    AllFormNoShow();
    showElement("PlayerStateForm", true);
}