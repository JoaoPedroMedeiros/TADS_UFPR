<?php

  class Resultado {
    
    function calculaResultado($nome, $identificador, $categoria, $modalidade) {
      $sqlResultado =
        "SELECT                                                           \n".
        "  (SELECT                                                        \n".
        "     COUNT(*) + 1                                                \n".
        "   FROM                                                          \n".
        "     Participacao P                                              \n".
        "   WHERE                                                         \n".
        "       P.nr_tempfi - P.nr_tempin < Par.nr_tempfi - Par.nr_tempin \n".
        "   AND Cat.cd_categ = P.cd_categ) nr_pos,                        \n".
        "  Par.nr_ident  ,                                                \n".
        "  Atl.nm_atleta ,                                                \n".
        "  Mo.ds_mod     ,                                                \n".
        "  Cat.ds_categ  ,                                                \n".
        "  nr_tempin     ,                                                \n".
        "  nr_tempfi     ,                                                \n".
        "  nr_dist / ((nr_tempfi - nr_tempin) / 10000) nr_velmed          \n".
        "FROM                                                             \n".
        "  Participacao Par                                               \n".
        "  INNER JOIN Atleta Atl ON (                                     \n".
        "    Par.cd_atleta = Atl.cd_atleta                                \n".
        "  )                                                              \n".
        "  INNER JOIN Modalidade Mo ON (                                  \n".
        "    Par.cd_mod = Mo.cd_mod                                       \n".
        "  )                                                              \n".
        "  INNER JOIN Categoria Cat ON (                                  \n".
        "    Par.cd_categ = Cat.cd_categ                                  \n".
        "  )                                                              \n".
        "WHERE                                                            \n".
        "    1 = 1                                                        \n";
        
        if ($nome != null)
          $sqlResultado = $sqlResultado . "AND Atl.nm_atleta like '". $nome ."%'\n";
        if ($identificador != null)
          $sqlResultado = $sqlResultado . "AND Par.nr_ident = ". $identificador ."\n";
        if ($categoria != null)
          $sqlResultado = $sqlResultado . "AND Cat.cd_categ = ". $categoria ."\n";
        if ($modalidade != null)
          $sqlResultado = $sqlResultado . "AND Mo.cd_mod = ". $modalidade ."\n";
        
        $sqlResultado = $sqlResultado.
          "ORDER BY                                                         \n".
          "  Cat.cd_categ,                                                  \n".
          "  nr_tempfi - nr_tempin                                          \n";
      
      return DBFactory::getQuery()->resultAsObject($sqlResultado) ;
    }
  }
?>