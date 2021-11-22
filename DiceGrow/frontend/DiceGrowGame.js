const FORM_NAMES = [
    "LoginForm",
    "SignUpForm",
    "PlayerStateForm",
    "RollDiceForm",
    "BattleReadyForm",
    "BattleForm"
];

var currentTurn;

// �ھ� ���
let coreModule = null;

// ������ �ε� �� �ʱ�ȭ
function initializePage() {
    console.log("���� �ʱ�ȭ");

    if (coreModule === null) {
        Module({ dynamicLibraries: ['DiceGrow_Core.wasm'] }).
            then((result) => {
                coreModule = result;
            });
    }

    AllFormNoShow();
    showElement("LoginForm", true);
}

// ��� Form ����
function AllFormNoShow() {

    const arrayLength = FORM_NAMES.length;

    for (var formIdx = 0; formIdx < arrayLength; ++formIdx) {
        showElement(FORM_NAMES[formIdx], false);
    }
}


//-------------------------
//       Js ���� �Լ�
//-------------------------

// ����� display ���¸� �����Ѵ�.
function showElement(elementId, show) {
    const element = document.getElementById(elementId);
    element.style.display = (show ? "" : "none");
}

// Text �� ����
function changeSpanText(elementId, str) {
    const element = document.getElementById(elementId);
    element.innerHTML = str;
}

// string format �Լ� �ܾ��...
function format() {
    var args = Array.prototype.slice.call(arguments, 1);
    return arguments[0].replace(/\{(\d+)\}/g, function (match, index) { return args[index]; });
}

//-------------------------
//       �α��� Form
//-------------------------

// �α��� ��ư Ŭ��
function OnClicked_LoginButton() {

    // �ھ� ��� �ʱ�ȭ
    coreModule._Init();

    AllFormNoShow();
    showElement("PlayerStateForm", true);

    RefreshPlayerStateUI();
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

// �÷��̾� ���� UI ����
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

// HP ����
function RefreshHPUI() {
    var hp = coreModule._Get_Player_HP();
    var max_hp = coreModule._Get_Player_MaxHP();
    changeSpanText("label-hp-value-text", format('[{0}/{1}]', hp, max_hp));
}

// �ֻ��� ����
function RefreshDiceSlotUI() {
    for (var index = 0; index < 6; ++index) {
        var dice_value = coreModule._Get_Player_Dice(index);
        changeSpanText("text-dice-value-" + index, format('{0}', dice_value));
    }
}

// Level Point �� [+]��ư ����
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

// MaxHP ���� ��ư
function OnClicked_MaxHPIncreaseButton() {
    coreModule._IncreaseMaxHP();
    RefreshHPUI();
    OnOffPlusButtons();
}
// �ֻ��� �� ���� ��ư
function OnClicked_DiceValueIncreaseButton(slot) {
    coreModule._IncreaseDiceValue(slot);
    RefreshDiceSlotUI();
    OnOffPlusButtons(); 
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

    // ���� �ֻ��� �� ���� �� ȹ��
    var point = coreModule._Get_Random_Dice_Point();
    console.log(point);
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