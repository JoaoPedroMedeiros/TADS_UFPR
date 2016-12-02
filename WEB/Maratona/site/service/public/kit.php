<?php
  
  // Recupera as classes de conexão com o banco de dados
  require_once('../private/conn/DBFactory.php');
  require_once('../private/conn/JSONFormatter.php');
  require_once('../private/conn/JSONUtil.php');
  require_once('../private/entity/Item.php');
  require_once('../private/entity/Kit.php');
  
  class JSONFormatterKit implements JSONFormatter {
    
    public function format($conn, $result) {
      
      $kits = array();
      $lastKit = null;
      $countItens = 0;
      $countKits = 0;
      
      for ($i=0; $i < $conn->rowsNumber($result); $i++) {
        
        $obj = $conn->fetchObject($result);
        
        if ($lastKit == null || $lastKit->cd_kit != $obj->cd_kit) {
          $countItens = 0;
          
          $lastKit = new Kit($obj->cd_kit, $obj->ds_kit);
          $lastKit->itens = array();
          $lastKit->itens[$countItens++] = new Item($obj->cd_item, $obj->ds_item);
          
          $kits[$countKits++] = $lastKit;
        }
        else
          $lastKit->itens[$countItens++] = new Item($obj->cd_item, $obj->ds_item);
      }
      
      echo json_encode($kits);
    }
  };
  
  //Recupera os parâmetros da requisição
  $param = JSONUtil::parameters($_SERVER);
  //Coloca como código da maratona se precisar.
  $cd_marat = sizeof($param) > 0 ? $param[0] : 1; 
  
  $sql = 
    "SELECT                                \n
       kit.cd_kit,                         \n
       kit.ds_kit,                         \n
       item.cd_item,                       \n
       item.ds_item                        \n
     FROM                                  \n
       kit                                 \n
       INNER JOIN maratona_kits ON (       \n
         maratona_kits.cd_kit = kit.cd_kit \n
       )                                   \n
       INNER JOIN kit_items ON (           \n
         kit.cd_kit = kit_items.cd_kit     \n
       )                                   \n
       INNER JOIN item ON (                \n
         kit_items.cd_item = item.cd_item  \n
       )                                   \n
     WHERE                                 \n
       cd_marat = + " . $cd_marat . "      \n";
  
  //Executa a consulta
  DBFactory::getQuery()->execFormat($sql, new JSONFormatterKit());
?>