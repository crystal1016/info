<?php

function countDays($dateInString) {

    // Write your code here
    $date_time = explode('.', $dateInString);

    if(count($date_time) == 3 && checkdate($date_time[0], $date_time[1], $date_time[2])){

        $formatted_date = $date_time[2].'-'.$date_time[0].'-'.$date_time[1].'00:00:00';

        $diff = strtotime($formatted_date) - strtotime($date_time[2].'-01-01 00:00:00');

        echo round($diff/86400)+1;

    } else {

        echo 'Bad format';

    }
    // To print results to the standard output you can use print
    // Example:
    // print "Hello world!";

}

// Do NOT call the countDays function in the code
// you write. The system will call it automatically.

?>