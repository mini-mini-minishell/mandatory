#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	check_arguments(argc, argv);  //예외처리 하는곳
	init_parsing(envp);
	// 파싱부 (파싱 테이블 + 트리 구현)
		// lexer : 토큰 나누는 곳
		// parser : 트리에 저장하고 트리를 만듦, 테이블 구현
	// 프롬프트 띄우기
	// 실행부(bulit-in, executable)
	return (0);
}

