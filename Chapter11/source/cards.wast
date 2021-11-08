 (module
	(import "env" "_GenerateCards"		(func $GenerateCards (param i32 i32 i32)))
	(import "env" "_FlipCard"			(func $FlipCard (param i32 i32 i32)))
	(import "env" "_RemoveCards"		(func $RemoveCards (param i32 i32 i32 i32)))
	(import "env" "_LevelComplete"		(func $LevelComplete (param i32 i32)))
	(import "env" "_Pause"				(func $Pause (param i32 i32)))

	(import "env" "memory" (memory $memory 256))
	(import "env" "_SeedRandomNumberGenerator" (func $SeedRandomNumberGenerator))
	(import "env" "_GetRandomNumber" (func $GetRandomNumber(param i32) (result i32)))
	(import "env" "_malloc" (func $malloc (param i32)(result i32)))
	(import "env" "_free" (func $free (param i32)))

	(global $MAX_LEVEL i32 (i32.const 3))
	(global $cards (mut i32) (i32.const 0))

	(global $current_level (mut i32)(i32.const 0))
	(global $rows (mut i32)(i32.const 0))
	(global $columns (mut i32)(i32.const 0))
	(global $matches_remaining (mut i32)(i32.const 0))

	(global $first_card_row (mut i32) (i32.const 0))
	(global $first_card_column (mut i32) (i32.const 0))
	(global $first_card_value (mut i32) (i32.const 0))
	(global $second_card_row (mut i32) (i32.const 0))
	(global $second_card_column (mut i32) (i32.const 0))
	(global $second_card_value (mut i32) (i32.const 0))

	(global $execution_paused (mut i32)(i32.const 0))

	(export "_CardSelected" (func $CardSelected))
	(export "_SecondCardSelectedCallBack" (func $SecondCardSelectedCallBack))
	(export "_ReplayLevel" (func $ReplayLevel))
	(export "_PlayNextLevel" (func $PlayNextLevel))

	(start $main)

	(func $InitializeRowsAndColumns (param $level i32)
		get_local $level
		i32.const 1
		i32.eq
		if
			i32.const 2
			set_global $rows
			i32.const 2
			set_global $columns
		end

		get_local $level
		i32.const 2
		i32.eq
		if
			i32.const 2
			set_global $rows
			i32.const 3
			set_global $columns
		end

		get_local $level
		i32.const 3
		i32.eq
		if
			i32.const 2
			set_global $rows
			i32.const 4
			set_global $columns
		end
	)

	(func $ResetSelectedCardValues
		i32.const -1
		set_global $first_card_row
		
		i32.const -1
		set_global $first_card_column
		
		i32.const -1
		set_global $first_card_value
		
		i32.const -1
		set_global $second_card_row
		
		i32.const -1
		set_global $second_card_column
		
		i32.const -1
		set_global $second_card_value
	)

	(func $InitializeCards (param $level i32) (local $count i32)
		get_local $level
		set_global $current_level

		get_local $level
		call $InitializeRowsAndColumns

		call $ResetSelectedCardValues

		get_global $rows
		get_global $columns
		i32.mul
		set_local $count

		get_local $count
		i32.const 2
		i32.div_s
		set_global $matches_remainig

		get_local $count
		i32.const 2
		i32.shl
		call $malloc
		set_global $cards

		get_local $count
		call $PopulateArray

		get_local $count
		call $ShuffleArray
	)


 )