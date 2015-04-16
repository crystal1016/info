<?php

function fibonacci($n) {

    // Write your code here
    $arrs = array(0,1,1);

    for($i=2 ; $i<=$n ; $i++){
    
        $a = (isset($arrs[ (int)$i-2 ]))?$arrs[ (int)$i-2 ]:0;
        
        $b = (isset($arrs[ (int)$i-1 ]))?$arrs[ (int)$i-1 ]:0;
        
        $c = ($a+$b);
    
        if($c<0){
        
            $c = 0;
        
        }
    
        $arrs[$i] = $c;
    
    }
    
    echo $arrs[ (int)$n-1 ];
    // To print results to the standard output you can use print
    // Example:
    // print "Hello world!";

}

// Do NOT call the fibonacci function in the code
// you write. The system will call it automatically.

?>