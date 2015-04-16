<?php

function fantastic3($n) {
    $arrs = array(0,1,1,1);

    for($i=3 ; $i<=$n ; $i++){
    
        $a = (isset($arrs[ (int)$i-3 ]))?$arrs[ (int)$i-3 ]:0;
        
        $b = (isset($arrs[ (int)$i-2 ]))?$arrs[ (int)$i-2 ]:0;
        
        $c = (isset($arrs[ (int)$i-1 ]))?$arrs[ (int)$i-1 ]:0;
        
        $d = ($a+$b+$c)-1;
    
        if($d<0){
        
            $d = 0;
        
        }
    
        $arrs[$i] = $d;
    
    }
    
    echo $arrs[ (int)$n-1 ];
    
}

// Do NOT call the fantastic3 function in the code
// you write. The system will call it automatically.

?>