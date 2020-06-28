# base-files version 4.0-6
# ~/.bash_profile: executed by bash(1) for login shells.

# The latest version as installed by the Cygwin Setup program can
# always be found at /etc/defaults/etc/skel/.bash_profile

# Modifying /etc/skel/.bash_profile directly will prevent
# setup from updating it.

# The copy in your home directory (~/.bash_profile) is yours, please
# feel free to customise it to create a shell
# environment to your liking.  If you feel a change
# would be benifitial to all, please feel free to send
# a patch to the cygwin mailing list.

# User dependent .bash_profile file

# source the users bashrc if it exists
if [ -f "${HOME}/.bashrc" ] ; then
  source "${HOME}/.bashrc"
fi

# Set PATH so it includes user's private bin if it exists
# if [ -d "${HOME}/bin" ] ; then
#   PATH="${HOME}/bin:${PATH}"
# fi

# Set MANPATH so it includes users' private man if it exists
# if [ -d "${HOME}/man" ]; then
#   MANPATH="${HOME}/man:${MANPATH}"
# fi

# Set INFOPATH so it includes users' private info if it exists
# if [ -d "${HOME}/info" ]; then
#   INFOPATH="${HOME}/info:${INFOPATH}"
# fi

export JAVA_HOME="${HOME}/java"

export HADOOP_HOME="/cygdrive/d/lib/hadoop-0.20.2-cdh3u1"

#export HIVE_INSTALL="/cygdrive/d/lib/hive-0.7.1-bin"

export HBASE_HOME="/cygdrive/d/lib/hbase-0.90.3-cdh3u1"

export PATH="${JAVA_HOME}/bin:${HADOOP_HOME}/bin:${HBASE_HOME}/bin:${PATH}"
