<?php

  class Item {
    
    public $cd_item;
    public $ds_item;

    public function __construct($cd_item, $ds_item) {
      
      $this->cd_item = $cd_item;
      $this->ds_item = $ds_item;
    }
  }
?>

