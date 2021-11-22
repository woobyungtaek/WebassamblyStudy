const FORM_NAMES = [
    "LoginForm",
    "SignUpForm",
    "PlayerStateForm",
    "RollDiceForm",
    "BattleReadyForm",
    "BattleForm"
];

var currentTurn;

// 코어 모듈
let coreModule = null;

// 페이지 로드 시 초기화
function initializePage() {
    console.log("게임 초기화");

    if (coreModule === null) {
        Module({ dynamicLibraries: ['DiceGrow_Core.wasm'] }).
            then((result) => {
                coreModule = result;
            });
    }

    AllFormNoShow();
    showElement("LoginForm", true);
}

// 모든 Form 끄기
function AllFormNoShow() {

    const arrayLength = FORM_NAMES.length;

    for (var formIdx = 0; formIdx < arrayLength; ++formIdx) {
        showElement(FORM_NAMES[formIdx], false);
    }
}


//-------------------------
//       Js 유용 함수
//-------------------------

// 요소의 display 상태를 변경한다.
function showElement(elementId, show) {
    const element = document.getElementById(elementId);
    element.style.display = (show ? "" : "none");
}

// Text 값 변경
function changeSpanText(elementId, str) {
    const element = document.getElementById(elementId);
    element.innerHTML = str;
}

// string format 함수 긁어옴...
function format() {
    var args = Array.prototype.slice.call(arguments, 1);
    return arguments[0].replace(/\{(\d+)\}/g, function (match, index) { return args[index]; });
}

//-------------------------
//       로그인 Form
//-------------------------

// 로그인 버튼 클릭
function OnClicked_LoginButton() {

    // 코어 모듈 초기화
    coreModule._Init();

    AllFormNoShow();
    showElement("PlayerStateForm", true);

    RefreshPlayerStateUI();
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

// 플레이어 정보 UI 갱신
function RefreshPlayerStateUI() {
    OnOffPlusButtons();

    RefreshHPUI();

    var lv = coreModule._Get_Player_Level();
    changeSpanText("label-level-value-text", format('{0}', lv));

    var exp = coreModule._Get_Player_Exp(); 
    var max_exp = coreModule._Get_Player_MaxExp();
    changeSpanText("label-exp-value-text", format('[{0}/{1}]', exp, max_exp));

    RefreshDiceSlotUI();
}

// HP 갱신
function RefreshHPUI() {
    var hp = coreModule._Get_Player_HP();
    var max_hp = coreModule._Get_Player_MaxHP();
    changeSpanText("label-hp-value-text", format('[{0}/{1}]', hp, max_hp));
}

// 주사위 갱신
function RefreshDiceSlotUI() {
    for (var index = 0; index < 6; ++index) {
        var dice_value = coreModule._Get_Player_Dice(index);
        changeSpanText("text-dice-value-" + index, format('{0}', dice_value));
    }
}

// Level Point 및 [+]버튼 갱신
function OnOffPlusButtons() {
    var lv_point = coreModule._Get_Player_LevelPoint();
    changeSpanText("label-levelpoint-value-text", format('{0}', lv_point));

    if (lv_point === 0) {
        showElement("button-maxhp-increase", false);

        for (var index = 0; index < 6; ++index) {
            showElement("button-dice-increase-" + index, false);
        }
    }
    else {
        showElement("button-maxhp-increase", true);

        for (var index = 0; index < 6; ++index) {
            showElement("button-dice-increase-" + index, true);
        }
    }

}

// MaxHP 증가 버튼
function OnClicked_MaxHPIncreaseButton() {
    coreModule._IncreaseMaxHP();
    RefreshHPUI();
    OnOffPlusButtons();
}
// 주사위 값 증가 버튼
function OnClicked_DiceValueIncreaseButton(slot) {
    coreModule._IncreaseDiceValue(slot);
    RefreshDiceSlotUI();
    OnOffPlusButtons(); 
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

    // 랜덤 주사위 값 추출 후 획득
    var point = coreModule._Get_Random_Dice_Point();
    console.log(point);
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