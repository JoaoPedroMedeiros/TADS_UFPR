<?php

  class JSONUtil {
    
    public static function parameters($server) {
      
      if (array_key_exists('PATH_INFO', $server))
        return explode('/', trim($server['PATH_INFO'],'/'));
      return array();
    }
  }
?>