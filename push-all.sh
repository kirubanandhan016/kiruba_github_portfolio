#!/usr/bin/env bash
set -euo pipefail

OWNER="kirubanandhan016"
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

command -v git >/dev/null || { echo "git is required"; exit 1; }
command -v gh >/dev/null || { echo "GitHub CLI (gh) is required"; exit 1; }
gh auth status >/dev/null || { echo "Run: gh auth login"; exit 1; }

repos=(
  "embedded-laser-mesh-disaster-communication"
  "arduino-underground-cable-fault-detection"
  "esp32-cam-object-detection"
  "c-image-steganography-lsb"
  "c-address-book"
  "linux-minishell-c"
)

for repo in "${repos[@]}"; do
  dir="$ROOT/$repo"
  cd "$dir"

  if ! gh repo view "$OWNER/$repo" >/dev/null 2>&1; then
    gh repo create "$OWNER/$repo" --public --description "Professional embedded / C / Linux project portfolio repository"
  fi

  if [ ! -d .git ]; then
    git init
  fi

  git branch -M main
  git add .
  git commit -m "Initial professional project implementation" || true

  git remote remove origin 2>/dev/null || true
  git remote add origin "https://github.com/$OWNER/$repo.git"
  git push -u origin main

  echo "Published: https://github.com/$OWNER/$repo"
done

echo "All repositories processed."
