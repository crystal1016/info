<?php

function changeNickname($oldNickname, $newNickname, $users){

	$valid = preg_match('/^(([^0-9])+([A-Za-z0-9\$\#\<\>\-\_]+))$/i', $newNickname, $matches);

	if($valid == true){

		$old_found = false;

		$new_exists = false;

		foreach($users as $id => $user){

			if($user['nickname'] == $oldNickname){

				$old_found = true;

			}

			if($user['nickname'] == $newNickname){

				$new_exists = true;

			}

		}

		if($old_found == true && $new_exists == false){

			echo 'Your nickname has been changed from '.$oldNickname.' to '.$newNickname;

		} else {

			echo 'Failed to update';

		}

	} else {

		echo 'Failed to update';

	}

}

// Do NOT call the changeNickname function in the code

// you write. The system will call it automatically.

?>