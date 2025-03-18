// No2337.move-pieces-to-obtain-a-string

func canChange(start string, target string) bool {
	n := len(start)

	i, j := 0, 0
	for i < n && j < n {
		// skip '_'
		for i < n && start[i] == '_' {
			i++
		}
		for j < n && target[j] == '_' {
			j++
		}

		// compare start[i] == target[j]
		if i < n && j < n {
			if start[i] != target[j] {
				return false
			}
			c := start[i]
			if c == 'L' && i < j || c == 'R' && i > j {
				return false
			}
			i++
			j++
		}
	}

	// others: i < n, j == n, compare remain are '_'
	for i < n {
		if start[i] != '_' {
			return false
		}
		i++
	}

	// others: i == n, j < n, compare remain are '_'
	for j < n {
		if target[j] != '_' {
			return false
		}
		j++
	}

	return true
}