<?php

function maskCustom($format, $str) {

  $ostr = str_replace(" ", "", $str);

  for($i=0; $i < strlen($ostr); $i++)
    $format[strpos($format,"#")] = $str[$i];

  return $format;
}

 function maskCPF($str) {
  return maskCustom('###.###.###-##', $str);
}

?>