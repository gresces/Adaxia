function darkMode() {
  const themeToggle = document.getElementById('theme-toggle');
  const themeIcon = document.getElementById('theme-icon');

  // 检查本地存储或系统偏好
  const currentTheme = document.documentElement.getAttribute('data-theme');
  const savedTheme = localStorage.getItem('theme');
  const systemPrefersDark = window.matchMedia('(prefers-color-scheme: dark)').matches;

  // 应用主题
  function applyTheme(theme) {
    document.documentElement.setAttribute('data-theme', theme);
    themeIcon.textContent = theme === 'dark' ? '[bright]' : '[dark]';
  }

  // 初始化主题
  if (savedTheme != currentTheme) {
    applyTheme(savedTheme);
  } else if (systemPrefersDark) {
    applyTheme('dark');
  }

  // 切换主题
  themeToggle.addEventListener('click', function() {
    const currentTheme = document.documentElement.getAttribute('data-theme');
    const newTheme = currentTheme === 'dark' ? 'light' : 'dark';
    applyTheme(newTheme);
    localStorage.setItem('theme', newTheme);
  });
}

document.addEventListener('DOMContentLoaded', darkMode);