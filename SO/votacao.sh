#!/bin/bash

#Script para Votacao

#Chamada do processo
processo

processo() {

    #Inicialização das variáveis de contagem de votos
    n=0
	a=0
	b=0
	c=0
	d=0
	e=0
	f=0
	g=0
	h=0
	i=0
	j=0	
	#Entrada do nome dos 10 candidatos
	echo "Digite o nome dos 10 candidatos participantes."
	read canda
	read candb
	read candc
	read candd
	read cande
	read candf
	read candg
	read candh
	read candi
	read candj
	echo "Deseja comecar a eleicao?"
	echo "Digite 1 para Sim e 2 para Nao."
	read se
	# Se o usuário decidir por iniciar a votação, a função "votacao" é chamada
	if [ $se == "1" ]; then
    		clear
    		votacao
    # Senão, o processo é chamado recursivamente.
	else
    		processo
	fi

	function segturno(){
	    # Interface para segundo turno
	    echo "Digite o nome dos dois candidatos participantes do Segundo Turno da Eleição."
		read candx
		read candy
		echo "Deseja comecar a eleição?"
		echo "Digite 1 para Sim e 2 para Nao."
		read sn
		if [ $sn == "1" ]; then
	    		clear
	    		votacaosegturno
		else
	    		segturno # Recursividade da função
		fi
	}

	function votacaosegturno(){
		tat=$((tat+1)) # Total de votos
		#informação do número referente à cada candidato
		echo "Para votar digite o numero de um dos candidatos relacionados:"
		echo "0. Anular Voto"
		echo "1. Candidato" $candx
		echo "2. Candidato" $candy
		echo
		read cond
		# Validação do voto para mostrar da mensagem
		if [ $cond == "0" ] || [ $cond == "1" ] || [ $cond == "2" ]; then
			echo -e  "\033[01;32m Voto confirmado. \033[01;37m"
			aplay somvoto.wav -q
		fi
		case $cond in					
			0) n=$((n+1));;
			1) x=$((x+1));;
			2) y=$((y+1));;
			R) resultadosegturno;;
			*) echo -e "\033[01;31m Opcao invalida, tente novamente! \033[01;37m"
		esac
	    sleep 2
		clear
    	votacaosegturno # Chamada recursiva da função até que o usuário queira ver o resultado
	}

	function resultadosegturno(){
		echo "Resultado da votacao do Segundo Turno:"		
		echo
		echo "O candidato" $candx "recebeu" $x "votos."
		echo "O candidato" $candy "recebeu" $y "votos."
		echo "Votos Nulos:" $n "votos."
		echo "Total de votos:" $tot
		echo "Total de votos no Segundo Turno:" $tat
		echo
		echo	
		if [ $x -gt $y ]; then
			echo "O Candidato" $candx "foi eleito com" $x "votos."	
		elif [ $y -gt $x ]; then
			echo "O Candidato" $candy "foi eleito com" $y "votos."	
		else
			echo "Houve empate na votacao do Segunto Turno. Digite 1 para continuar a votacao ou digite 2 para encerrar."
			read si
			if [ $si == "1" ]; then	
				clear
				votacaosegturno
			else 
	    			exit
			fi			
		fi
		echo "Deseja reiniciar todo o processo de Eleicao?"
		echo "Digite 1 para Sim e 2 para Nao."
		read sn
		if [ $sn == "1" ]; then
			x=0    		
			y=0		
			n=0
			a=0
			b=0
			c=0
			d=0
			e=0
			f=0
			g=0
			h=0
			i=0
			j=0		
			tot=0		
			clear
			processo
		else 
	    		exit
		fi			
	}

	function votacao(){
		# INFORMAÇÃO DO NÚMERO DE CADA CANDIDATO
		tot=$((tot+1))		#contador para obter o total de votos
		echo "Para votar digite o numero de um dos candidatos relacionados:"  #leitura dos votos
		echo "0. Anular Voto"
		echo "1. Candidato" $canda
		echo "2. Candidato" $candb
		echo "3. Candidato" $candc
		echo "4. Candidato" $candd
		echo "5. Candidato" $cande
		echo "6. Candidato" $candf
		echo "7. Candidato" $candg
		echo "8. Candidato" $candh
		echo "9. Candidato" $candi
		echo "10. Candidato" $candj
		echo
		read cond
		# Validação do voto para mostrar a mensagem de voto válido
		if [ $cond == "0" ] || [ $cond == "1" ] || [ $cond == "2" ] || [ $cond == "3" ] || [ $cond == "4" ] || [ $cond == "5" ] || [ $cond == "6" ] ||
		   [ $cond == "7" ] || [ $cond == "8" ] || [ $cond == "9" ] || [ $cond == "10" ]; then
			echo -e  "\033[01;32m Voto confirmado. \033[01;37m" #Mensagem de confirmação do voto (verde)
			aplay somvoto.wav -q #Som da urna
		fi	
		#contador dos votos referente a cada candidato
		case $cond in 
			0) n=$((n+1));;
			1) a=$((a+1));;
			2) b=$((b+1));;
			3) c=$((c+1));;
			4) d=$((d+1));;
			5) e=$((e+1));;
			6) f=$((f+1));;
			7) g=$((g+1));;
			8) h=$((h+1));;
			9) i=$((i+1));;
			10) j=$((j+1));;
			R) resultado;;		#ao digitar a letra R em maiusculo, é executado	a função resultado				
			*) echo -e "\033[01;31m Opcao invalida, tente novamente! \033[01;37m" #Mensagem de erro (vermelho)
		esac
		sleep 2 #Pausa para o clear
		clear
	    votacao
	}

	function resultado() {
		echo "Resultado da votacao:" #Mostra quantos votos cada candidato recebeu
		echo
		echo "O candidato" $canda "recebeu" $a "votos."
		echo "O candidato" $candb "recebeu" $b "votos."
		echo "O candidato" $candc "recebeu" $c "votos."
		echo "O candidato" $candd "recebeu" $d "votos."
		echo "O candidato" $cande "recebeu" $e "votos."
		echo "O candidato" $candf "recebeu" $f "votos."
		echo "O candidato" $candg "recebeu" $g "votos."
		echo "O candidato" $candh "recebeu" $h "votos."
		echo "O candidato" $candi "recebeu" $i "votos."
		echo "O candidato" $candj "recebeu" $j "votos."
		echo "Votos Nulos:" $n "votos."
		echo "Total de votos:" $tot
		echo 
		echo
		# VERIFICAÇÃO DO CANDIDATO VENCEDOR
		if [ $a -gt $b ] && [ $a -gt $c ] && [ $a -gt $d ] && [ $a -gt $e ] && [ $a -gt $f ] && [ $a -gt $g ] && [ $a -gt $h ] && [ $a -gt $i ] && [ $a -gt $j ]; then
			echo "O Candidato" $canda "foi eleito com" $a "votos."
		elif [ $b -gt $a ] && [ $b -gt $c ] && [ $b -gt $d ] && [ $b -gt $e ] && [ $b -gt $f ] && [ $b -gt $g ] && [ $b -gt $h ] && [ $b -gt $i ] && [ $b -gt $j ]; then	
			echo "O Candidato" $candb "foi eleito com" $b "votos."		
		elif [ $c -gt $a ] && [ $c -gt $b ] && [ $c -gt $d ] && [ $c -gt $e ] && [ $c -gt $f ] && [ $c -gt $g ] && [ $c -gt $h ] && [ $c -gt $i ] && [ $c -gt $j ]; then	
			echo "O Candidato" $candc "foi eleito com" $c "votos."
		elif [ $d -gt $a ] && [ $d -gt $b ] && [ $d -gt $c ] && [ $d -gt $e ] && [ $d -gt $f ] && [ $d -gt $g ] && [ $d -gt $h ] && [ $d -gt $i ] && [ $d -gt $j ]; then	
			echo "O Candidato" $candd "foi eleito com" $d "votos."
		elif [ $e -gt $a ] && [ $e -gt $b ] && [ $e -gt $c ] && [ $e -gt $d ] && [ $e -gt $f ] && [ $e -gt $g ] && [ $e -gt $h ] && [ $e -gt $i ] && [ $e -gt $j ]; then	
			echo "O Candidato" $cande "foi eleito com" $e "votos."
		elif [ $f -gt $a ] && [ $f -gt $b ] && [ $f -gt $c ] && [ $f -gt $d ] && [ $f -gt $e ] && [ $f -gt $g ] && [ $f -gt $h ] && [ $f -gt $i ] && [ $f -gt $j ]; then	
			echo "O Candidato" $candf "foi eleito com" $f "votos."
		elif [ $g -gt $a ] && [ $g -gt $b ] && [ $g -gt $c ] && [ $g -gt $d ] && [ $g -gt $e ] && [ $g -gt $f ] && [ $g -gt $h ] && [ $g -gt $i ] && [ $g -gt $j ]; then	
			echo "O Candidato" $candg "foi eleito com" $g "votos."
		elif [ $h -gt $a ] && [ $h -gt $b ] && [ $h -gt $c ] && [ $h -gt $d ] && [ $h -gt $e ] && [ $h -gt $f ] && [ $h -gt $g ] && [ $h -gt $i ] && [ $h -gt $j ]; then	
			echo "O Candidato" $candh "foi eleito com" $h "votos."
		elif [ $i -gt $a ] && [ $i -gt $b ] && [ $i -gt $c ] && [ $i -gt $d ] && [ $i -gt $e ] && [ $i -gt $f ] && [ $i -gt $g ] && [ $i -gt $h ] && [ $i -gt $j ]; then	
			echo "O Candidato" $candi "foi eleito com" $i "votos."
		elif [ $j -gt $a ] && [ $j -gt $b ] && [ $j -gt $c ] && [ $j -gt $d ] && [ $j -gt $e ] && [ $j -gt $f ] && [ $j -gt $g ] && [ $j -gt $h ] && [ $j -gt $i ]; then	
			echo "O Candidato" $candj "foi eleito com" $j "votos."	
		else # Se nenhum candidato foi vitorioso, a função "segturno" é chamada.
			echo "Houve empate na votacao. Voce será direcionado para o Segundo Turno da eleicao."
			segturno
		fi		
		echo	
		echo "Deseja reiniciar a votacao?"
		echo "Digite 1 para Sim e 2 para Nao."
		read sn
		if [ $sn == "1" ]; then
	    	n=0
			a=0
			b=0
			c=0
			d=0
			e=0
			f=0
			g=0
			h=0
			i=0
			j=0		
			clear
			processo
		else 
	    		exit
		fi						#comando IF, ELIF, ELSE vai indicar o vencedor
	}
}


