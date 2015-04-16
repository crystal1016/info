<?php
function countDays($dateInString) {

    $date = explode('.', $dateInString);

    if(count($date) == 3 && checkdate($date[0], $date[1], $date[2])){

        $formatted_date = $date[2].'-'.$date[0].'-'.$date[1].'00:00:00';

        $diff = strtotime($formatted_date) - strtotime($date[2].'-01-01 00:00:00');

        echo round($diff/86400)+1;

    } else {

        echo 'Bad format';

    }

}

// Do NOT call the fantastic3 function in the code
// you write. The system will call it automatically.

?>