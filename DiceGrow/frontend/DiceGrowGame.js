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

    RefreshHPUI("label-hp-value-text");

    RefreshLvUI("label-level-value-text");

    var exp = coreModule._Get_Player_Exp();
    var max_exp = coreModule._Get_Player_MaxExp();
    changeSpanText("label-exp-value-text", format('[{0}/{1}]', exp, max_exp));

    RefreshDiceSlotUI();
}

function RefreshLvUI(ui_key) {
    var lv = coreModule._Get_Player_Level();
    changeSpanText(ui_key, format('{0}', lv));
}

// HP ����
function RefreshHPUI(ui_key) {
    var hp = coreModule._Get_Player_HP();
    var max_hp = coreModule._Get_Player_MaxHP();
    changeSpanText(ui_key, format('[{0}/{1}]', hp, max_hp));
}

// �ֻ��� ����
function RefreshDiceSlotUI() {
    for (var idx = 0; idx < 6; ++idx) {
        var dice_value = coreModule._Get_Player_Dice(idx);
        changeSpanText("text-dice-value-" + idx, format('{0}', dice_value));
    }
}

// Level Point �� [+]��ư ����
function OnOffPlusButtons() {
    var lv_point = coreModule._Get_Player_LevelPoint();
    changeSpanText("label-levelpoint-value-text", format('{0}', lv_point));

    if (lv_point === 0) {
        showElement("button-maxhp-increase", false);

        for (var idx = 0; idx < 6; ++idx) {
            showElement("button-dice-increase-" + idx, false);
        }
    }
    else {
        showElement("button-maxhp-increase", true);

        for (var idx = 0; idx < 6; ++idx) {
            showElement("button-dice-increase-" + idx, true);
        }
    }

}

// MaxHP ���� ��ư
function OnClicked_MaxHPIncreaseButton() {
    coreModule._IncreaseMaxHP();
    RefreshHPUI("label-hp-value-text");
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

    // ���� �غ� UI ����
    RefreshBattleReadyUI();
    showElement("BattleReadyForm", true);
}


//-------------------------
//     ���� �غ� Form
//-------------------------

function RefreshBattleReadyUI() {

    // ��Ʋ �غ� ���� �ʱ�ȭ
    coreModule._InitBattleArr();

    // HP ����
    RefreshHPUI("HP-value-label-player");

    // �ֻ��� ����Ʈ ����
    RefreshDicePointUI();

    // ����, ���ݷ� ����Ʈ ����
    RefreshAttackPointUI();
}

function RefreshDicePointUI() {
    var dp = coreModule._Get_Player_DicePoint();
    changeSpanText("DP-value-label-player", format('{0}', dp));
}

function RefreshAttackPointUI() {
    for (var idx = 0; idx < 4; ++idx) {
        changeSpanText(format('Attack-dec-enemy-{0}', idx + 1), format('{0}', coreModule._Get_Dec_Point_Player(idx)));
        changeSpanText(format('Attack-player-{0}', idx + 1), format('{0}', coreModule._Get_Attack_Point_Player(idx)));
    }
}

// ���Ժ� ��ư
function OnClicked_IncreaseButton(slotType, slotNum) {

    coreModule._IncreaseSlotPoint(slotType, slotNum - 1);

    RefreshDicePointUI();
    RefreshAttackPointUI();
}

function OnClicked_DecreaseButton(slotType, slotNum) {
    coreModule._DecreaseSlotPoint(slotType, slotNum - 1);

    RefreshDicePointUI();
    RefreshAttackPointUI();
}

// ���� ���� ��ư 
function OnClicked_BattleStartButton() {
    InitBattleForm();

    AllFormNoShow();
    showElement("BattleForm", true);
}

//-------------------------
//     ���� Form
//-------------------------

// ���� �ʱ�ȭ
function InitBattleForm() {
    currentTurn = 0;

    // ��� ���
    coreModule._InitBattleArr();

    // �÷��̾� ����, ü�� ����
    RefreshLvUI("Lv-value-player-battle-label");
    RefreshHPUI("HP-value-player-battle-label");

    // ���ݷ� ǥ�� ����
    RefreshAttackValueUI();
    RefreshDecreaseValueUI();
    RefreshAttackFinalValueUI();
    RefreshTurnResultValueUI();
}

// UI�� ����

// ���ݷ� ����
function RefreshAttackValueUI() {
    for (var idx = 0; idx < 4; ++idx) {
        changeSpanText(format('Attack-value-enemy-{0}', idx), format('{0}', coreModule._Get_Attack_Point_Enemy(idx)));
        changeSpanText(format('Attack-value-player-{0}', idx), format('{0}', coreModule._Get_Attack_Point_Player(idx)));
    }
}

// ���ݷ� ���� ����
function RefreshDecreaseValueUI() {
    for (var idx = 0; idx < 4; ++idx) {
        // ������ ���� �־���Ѵ�.
        changeSpanText(format('Decrease-value-player-{0}', idx), format('{0}', coreModule._Get_Dec_Point_Enemy(idx)));
        changeSpanText(format('Decrease-value-enemy-{0}', idx), format('{0}', coreModule._Get_Dec_Point_Player(idx)));
    }
}

// ���� ���ݷ� ����
function RefreshAttackFinalValueUI() {
    for (var idx = 0; idx < 4; ++idx) {
        changeSpanText(format('Attack-final-enemy-{0}', idx), format('{0}', coreModule._Get_Final_Attack_Enemy(idx)));
        changeSpanText(format('Attack-final-player-{0}', idx), format('{0}', coreModule._Get_Final_Attack_Player(idx)));
    }
}

// �� �� ��� ����
function RefreshTurnResultValueUI() {
    for (var idx = 0; idx < 4; ++idx) {
        var dmg = coreModule._Get_Turn_Result(idx);

        if (dmg > 0) {
            changeSpanText(format('Result-slot-turn-{0}', idx), '�¸�');
        }
        else if (dmg < 0) {
            changeSpanText(format('Result-slot-turn-{0}', idx), '�й�');
        }
        else {
            changeSpanText(format('Result-slot-turn-{0}', idx), '���º�');
        }

        changeSpanText(format('Damage-slot-turn-{0}', idx), format('{0}', dmg));
    }
}

// ���� �� ��ư
function OnClicked_ConfirmButton() {
    AllFormNoShow();

    // ���� ����� �����ͼ�
    // ���� ���� ����
    // �÷��̾� ���� â���� ���� ���ؾ���
    var battleResult = coreModule._Get_Battle_Result();

    if (battleResult === 0) {
        showElement("RollDiceForm", true);
    }
    else if (battleResult === 1) {
        showElement("PlayerStateForm", true);
    }
    else {
        // ���� ���� form
        showElement("PlayerStateForm", true);
    }
}