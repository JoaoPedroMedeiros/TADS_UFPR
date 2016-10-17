<?php

  class Kit {
    
    public $cd_kit;
    public $ds_kit;
    public $itens;

    public function __construct($cd_kit, $ds_kit) {
      
      $this->cd_kit = $cd_kit;
      $this->ds_kit = $ds_kit;
    }
  }
?>

